#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/voronoi/structures/EdgeData.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <unordered_map>

class Triangle : public Polygon{
private:
    Point circumcenter;
    Point calculateCircumcenter(std::vector<Point>& p);
public:
    Triangle();
    Triangle(std::vector<int> points, std::vector<Point>& p);
    Point getCircumcenter();
    int nextEdge(int center, EdgeData edge, std::unordered_map<Key, int, KeyHasher> edgeMap);
    int thirdPoint(EdgeData edge);
};

#endif


