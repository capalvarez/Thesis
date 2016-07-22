#include <models/Triangulation.h>
#include "TriangleMeshGenerator.h"


TriangleMeshGenerator::TriangleMeshGenerator(std::vector<Point>& point_list, Region region) {
    callTriangle(point_list, region);
    this->mesh = delaunayToVoronoi();
}

Mesh TriangleMeshGenerator::getMesh() {
    return this->mesh;
}

Triangulation TriangleMeshGenerator::getDelaunayTriangulation() {
    return Triangulation(this->meshPoints, this->triangles);
}

void TriangleMeshGenerator::callTriangle(std::vector<Point> &point_list, Region region) {
    struct triangulateio in, out;

    std::vector<Point> regionPoints = region.getRegionPoints();
    List<Point> pointList;
    pointList.push_list(point_list);
    std::vector<int> regionIndex = pointList.push_list(regionPoints);


    in.numberofpoints = pointList.size();
    in.pointlist = (REAL*)malloc(in.numberofpoints*2*sizeof(REAL));
    int points = 0;

    for(int i=0;i<pointList.size();i++){
        in.pointlist[points] = pointList.get(i).getX();
        in.pointlist[points+1] = pointList.get(i).getY();
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
        in.segmentlist[2*i] = regionIndex[segments[i].getFirst()];
        in.segmentlist[2*i+1] = regionIndex[segments[i].getSecond()];
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
        Triangle triangle (triangle_points, this->meshPoints);
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
    for(int i=0;i<this->meshPoints.size(); i++) {
        List<int> cellPoints;
        Point regionCenter = this->meshPoints[i];
        EdgeData init_edge = this->edges[this->points[i].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        int index1 = voronoiPoints.push_back(getCircumcenter(t1,this->points[i].edge,meshPoints));
        int index2 = voronoiPoints.push_back(getCircumcenter(t2,this->points[i].edge,meshPoints));

        //TODO: Fix this!
        if(index1!=index2){
            voronoiEdges.push_back(Segment(index2,index1));
            cellPoints.push_back(index2);
        }

        cellPoints.push_back(index1);

        EdgeData edge = this->edges[triangles[t1].nextEdge(i, init_edge, edgeMap)];

        while(!edge.equals(init_edge)){
            t2 = t1;
            t1 = edge.t1!=t2? edge.t1 : edge.t2;

            int currentEdge = edgeMap[Key(edge.p1, edge.p2)];
            index1 = voronoiPoints.push_back(getCircumcenter(t1,currentEdge,meshPoints));
            index2 = voronoiPoints.push_back(getCircumcenter(t2,currentEdge,meshPoints));

            if(index1!=index2){
                voronoiEdges.push_back(Segment(index2, index1));
                cellPoints.push_back(index2);
            }

            cellPoints.push_back(index1);

            if(t1!=-1){
                edge = this->edges[triangles[t1].nextEdge(i, edge, edgeMap)];
            }else{
                break;
            }
        }

        if(edge.t2==-1){
            int firstPoint = cellPoints.get(0);
            int lastPoint = cellPoints.get(cellPoints.size()-1);

            if(geometry_functions::collinear(voronoiPoints.get(firstPoint),regionCenter,voronoiPoints.get(lastPoint))){
                voronoiEdges.push_back(Segment(lastPoint, firstPoint));
            } else{
                int regionIndex = voronoiPoints.push_back(regionCenter);
                cellPoints.push_back(regionIndex);

                voronoiEdges.push_back(Segment(lastPoint, regionIndex));
                voronoiEdges.push_back(Segment(regionIndex, firstPoint));
            }
        }

        std::vector<Point> pointList = voronoiPoints.getList();
        std::vector<int> cellPointsList = cellPoints.getList();

        this->voronoiCells.push_back(Polygon(cellPointsList, pointList));
    }

    std::vector<Point> points = this->voronoiPoints.getList();
    std::vector<Polygon> cells = this->voronoiCells.getList();
    std::vector<Segment> edges = this->voronoiEdges.getList();

    return Mesh(points, cells, edges);
}

Point TriangleMeshGenerator::getCircumcenter(int triangle, int edge, std::vector<Point> &points) {
    if(triangle!=-1){
        return this->triangles[triangle].getCircumcenter();
    }else{
        return Segment(this->edges[edge].p1, this->edges[edge].p2).middlePoint(points);
    }
}



