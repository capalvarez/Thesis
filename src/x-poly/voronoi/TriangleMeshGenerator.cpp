#include "TriangleMeshGenerator.h"
struct Key {
    int first;
    int second;

    Key(int f, int s){first=f; second=s;}

    bool operator==(const Key &other) const{
        return first == other.first && second == other.second ||
               first == other.second && second == other.first;
    }
};

struct KeyHasher {
    std::size_t operator()(const Key &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.first) + hash<int>()(k.second);
    }
};

TriangleMeshGenerator::TriangleMeshGenerator(std::vector<Point>& point_list, Region region) {
    callTriangle(point_list, region);
    this->mesh = delaunayToVoronoi();
}

Mesh TriangleMeshGenerator::getMesh() {
    return this->mesh;
}

void TriangleMeshGenerator::callTriangle(std::vector<Point> &point_list, Region region) {
    struct triangulateio in, out;

    std::vector<Point> regionPoints = region.getRegionPoints();
    in.numberofpoints = (int) point_list.size() + (int) regionPoints.size();
    in.pointlist = (REAL*)malloc(in.numberofpoints*2*sizeof(REAL));
    int points = 0;

    for(int i=0;i<point_list.size();i++){
        in.pointlist[points] = point_list[i].getX();
        in.pointlist[points+1] = point_list[i].getY();
        points+=2;
    }

    for(int i=0;i<regionPoints.size(); ++i) {
        in.pointlist[points] = regionPoints[i].getX();
        in.pointlist[points+1] = regionPoints[i].getY();
        points+=2;
    }

    in.numberofpointattributes = 1;
    in.pointattributelist = (REAL *) malloc(in.numberofpoints*in.numberofpointattributes*sizeof(REAL));
    for (int i=0;i<in.numberofpoints;i++){
        in.pointattributelist[i] = 0.0;
    }

    in.pointmarkerlist = (int *)NULL;

    std::vector<Segment> segments;
    region.getSegments(segments);

    in.numberofsegments = (int) segments.size();
    in.segmentlist = (int*)malloc(in.numberofsegments*2*sizeof(int));
    in.segmentmarkerlist = (int*) NULL;
    for(int i=0;i<segments.size();i++){
        in.segmentlist[2*i] = segments[i].getFirst() + (int) point_list.size();
        in.segmentlist[2*i+1] = segments[i].getSecond() + (int) point_list.size();
    }

    std::vector<Hole*> holes = region.getHoles();
    in.numberofholes = (int) holes.size();
    in.holelist = (REAL*)malloc(in.numberofholes*2*sizeof(REAL));
    for(int i=0;i<holes.size();i++){
        in.holelist[2*i] = holes[i]->getCenter().getX();
        in.holelist[2*i+1] = holes[i]->getCenter().getY();
    }

    in.numberofregions = 0;

    out.pointlist = (REAL *) NULL;
    out.pointattributelist = (REAL *) NULL;
    out.pointmarkerlist = (int *) NULL;
    out.trianglelist = (int *) NULL;
    out.triangleattributelist = (REAL *) NULL;
    out.neighborlist = (int *) NULL;
    out.segmentmarkerlist = (int *) NULL;
    out.segmentlist = (int *) NULL;
    out.edgelist = (int *) NULL;
    out.edgemarkerlist = (int *) NULL;

    char switches[5];
    sprintf(switches,"pzneD");
    triangulate(switches, &in, &out, (struct triangulateio *)NULL);

    std::unordered_map<Key, int, KeyHasher> edgeMap;

    for(int i=0;i<out.numberofpoints;i++){
        PointData data (i);
        this->points.push_back(data);
        this->meshPoints.push_back(Point(out.pointlist[i*2], out.pointlist[i*2+1]));
    }

    for(int i=0;i<out.numberofedges;i++) {
        EdgeData data(out.edgelist[2*i], out.edgelist[2*i+1]);
        this->edges.push_back(data);
        edgeMap.insert(std::make_pair(Key(out.edgelist[2*i], out.edgelist[2*i+1]),i));
        this->points[out.edgelist[2*i]].setEdge(i, out.edgemarkerlist[i]);
        this->points[out.edgelist[2*i+1]].setEdge(i, out.edgemarkerlist[i]);
    }

    for(int i=0;i<out.numberoftriangles;i++){
        std::vector<int> triangle_points = {out.trianglelist[3*i], out.trianglelist[3*i+1],
                                            out.trianglelist[3*i+2]};
        Triangle* triangle = new Triangle(triangle_points, this->meshPoints);
        int i1 = edgeMap[Key(out.trianglelist[3*i], out.trianglelist[3*i+1])];
        int i2 = edgeMap[Key(out.trianglelist[3*i+1], out.trianglelist[3*i+2])];
        int i3 = edgeMap[Key(out.trianglelist[3*i+2], out.trianglelist[3*i])];

        this->edges[i1].setTriangle(i);
        this->edges[i2].setTriangle(i);
        this->edges[i3].setTriangle(i);

        this->triangles.push_back(triangle);
    }
}

Mesh TriangleMeshGenerator::delaunayToVoronoi() {
    /*for(int i=0;i<this->meshPoints.size(); i++) {
        std::vector<int> cellPoints;
        Point regionCenter = this->meshPoints[i];
        EdgeData init_edge = this->edges[this->points[i].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        //Tomo ambos circumcentros, los meto en el vector
        //Uno los circumcentros y guardo este segmento en el vector
        //Pongo los indices de los circumcentros en el vector de cellPoints

        EdgeData edge = this->edges[t1.nextEdge()];

        while(t1!=-1 || edge!=init_edge){
            t1 = edge.t1;
            t2 = edge.t2;

            //Hago lo mismo que antes
            //actualizo edge
        }

        //Condicion de borde
        if(t1==-1){
            //Reviso si el primer punto, ultimo punto y regionCenter son colineales
            //si lo son, agrego el segmento (ultimo, primero)
            //si no lo son, agrego regionCenter a la region y agrego los segmentos
            //(ultimo, centro) y (centro, primero)
        }


        this->voronoiCells.push_back(Polygon(cellPoints, this->voronoiPoints));
    }
*/
    return Mesh();
}


Point TriangleMeshGenerator::getCircumcenter(int triangle, int edge, std::vector<Point> &points) {
    if(triangle!=-1){
        return this->triangles[triangle]->getCircumcenter();
    }else{
        return Segment(this->edges[edge].p1, this->edges[edge].p2).middlePoint(points);
    }
}



