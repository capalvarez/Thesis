#ifndef THESIS_POLYGON_H
#define THESIS_POLYGON_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/utilities/geometryFunctions.h>
#include <x-poly/utilities/convexHull.h>
#include <x-poly/models/basic/IndexSegment.h>
#include <utilities/Pair.h>

class Polygon {
protected:
    std::vector<int> points;
private:
    double diameter;
    double area;
    Point centroid;

    double calculateDiameter(std::vector<Point>& p);
    double calculateArea(std::vector<Point>& p);
    Point calculateCentroid(std::vector<Point>& p);
    void calculateHash();
public:
    Polygon(std::vector<int>& points, std::vector<Point>& p);
    Polygon(std::vector<Point>& p);
    Polygon(const Polygon &obj);
    Polygon();

    double getDiameter();
    double getArea();
    Point getCentroid();
    void getSegments(std::vector<IndexSegment>& segments);
    void getSegments(std::vector<IndexSegment> &segments, int offset);
    std::vector<int> getPoints() const;
    std::vector<Point> getPoints(std::vector<Point> p);
    int numberOfSides();
    bool operator==(const Polygon& other) const;
    bool operator<(const Polygon& other) const;
    std::string getString();

    void mutate(std::vector<Point>& p);
    void mutate(std::vector<int> points, std::vector<Point> p);
    void update(std::vector<Point> points);

    bool containsPoint(std::vector<Point>& p, Point point);
    bool inEdges(std::vector<Point>& p, Point point);
    double signedArea(std::vector<Point>& p);
    bool containsEdge(IndexSegment s);

    bool isConvex(std::vector<Point>& p);
    bool isClockwise(std::vector<Point>& p);
    bool isVertex(int index);
    bool isSelfIntersecting(std::vector<Point> points);
    std::size_t hash;
    void fixCCW(std::vector<Point> p);
    bool intersectsSegment(PointSegment segment, std::vector<Point> points);

    IndexSegment containerEdge(std::vector<Point>& p, Point point);
    void replace_segment(IndexSegment seg, std::vector<IndexSegment> segs, std::vector<Point> points);

    Pair<int> commonEdgesBorder(Polygon p);
    std::vector<IndexSegment> getAdjacentEdges(int i);
};

#endif