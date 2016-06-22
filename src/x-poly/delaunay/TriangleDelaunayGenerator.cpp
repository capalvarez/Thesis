#include "TriangleDelaunayGenerator.h"
#include <stdlib.h>
#include "lib/triangle.h"

TriangleDelaunayGenerator::TriangleDelaunayGenerator(std::vector<Point>& point_list, Region region) {
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

    Mesh* m = new Mesh();
    /*std::vector<Point_Data> points;
    std::vector<Edge_Data> edges;
    std::vector<Polygon> triangles;*/
//    std::unordered_map<Segment,int,struct {
//        std::size_t operator()(Segment& s) {
//            return std::hash<int>()(s.getFirst()) ^
//                    (std::hash<int>()(s.getSecond()) << 1);
//        }
//    }, struct {
//        bool operator()(Segment& s1, Segment& s2) {
//            return s1.getFirst() == s2.getFirst() && s1.getFirst() == s2.getSecond() ||
//                   s1.getSecond() == s2.getFirst() && s1.getFirst() == s2.getFirst();
//        }
//    }> segment_index;

    /*for(int i=0;i<out.numberofpoints;i++){
        struct Point_Data data;
        data.point = *new Point(out.pointlist[i*2], out.pointlist[i*2+1]);
        data.edge = -1;

        points.push_back(data);
    }

    for(int i=0;i<out.numberofedges;i++){
        Edge_Data data;
        data.edge = *new Segment(out.edgelist[i*2], out.edgelist[i*2+1]);
        data.polygon1 = -1;
        data.polygon2 = -1;

        edges.push_back(data);

        if(points[out.edgelist[i*2]].edge == -1 || out.edgemarkerlist[i*2]==1){
            points[out.edgelist[i*2]].edge = edges.size()-1;
        }*/

    //segment_index.insert({data.edge,edges.size() - 1});


    /*  for(int i=0;i<out.numberoftriangles;i++){
          //Polygon* newPolygon = new Polygon();

          //triangles.push_back(*newPolygon);
      }
  */
}

Mesh TriangleDelaunayGenerator::getDelaunayTriangulation() {
    return this->delaunay;
}
