#include "TriangleDelaunayGenerator.h"
#include <iostream>
#include <malloc.h>
#include "lib/triangle.h"
#include "../geometry/Region.h"
#include "../geometry/Segment.h"
#include "../geometry/Polygon.h"

TriangleDelaunayGenerator::TriangleDelaunayGenerator(std::vector<Point> point_list, Region region) {
    struct triangulateio in, out;

    in.numberofpoints = point_list.size();
    in.pointlist = (REAL*)malloc(in.numberofpoints*2*sizeof(REAL));
    in.pointmarkerlist = (int *)malloc(in.numberofpoints*sizeof(int));
    for(int i=0;i<point_list.size();i++){
        in.pointlist[i] = point_list[i].getX();
        in.pointlist[i+1] = point_list[i].getY();
        in.pointmarkerlist[i] = point_list[i].getBoundaryMarker();
    }

    in.numberofpointattributes = 0;

    std::vector<Segment> segments;
    region.getSegments(segments);

    in.numberofsegments = segments.size();
    in.segmentlist = (int*)malloc(in.numberofsegments*2*sizeof(int));
    for(int i=0;i<2*segments.size();i+=2){
        in.segmentlist[i] = segments[i].getFirst();
        in.segmentlist[i+1] = segments[i].getSecond();
    }

    std::vector<Hole> holes = region.getHoles();
    in.numberofholes = holes.size();
    in.holelist = (REAL*)malloc(in.numberofholes*2*sizeof(REAL));
    for(int i=0;i<2*holes.size();i+=2){
        in.holelist[i] = holes[i].getCenter().getX();
        in.holelist[i+1] = holes[i].getCenter().getY();
    }

    out.pointlist = (REAL *) NULL;
    out.trianglelist = (int *) NULL;
    out.neighborlist = (int *) NULL;
    out.segmentmarkerlist = (int *) NULL;

    out.edgelist = (int *) NULL;
    out.edgemarkerlist = (int *) NULL;

    triangulate("pneD", &in, &out, (struct triangulateio *)NULL);

    Mesh* m = new Mesh();
    std::vector<Point_Data> points;
    std::vector<Edge_Data> edges;
    std::vector<Polygon> triangles;
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

    for(int i=0;i<out.numberofpoints;i++){
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
        }

        //segment_index.insert({data.edge,edges.size() - 1});
    }

    for(int i=0;i<out.numberoftriangles;i++){
        //Polygon* newPolygon = new Polygon();

        //triangles.push_back(*newPolygon);
    }

}

Mesh TriangleDelaunayGenerator::getDelaunayTriangulation() {
    return this->delaunay;
}
