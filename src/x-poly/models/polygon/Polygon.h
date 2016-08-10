#ifndef THESIS_POLYGON_H
#define THESIS_POLYGON_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/utilities/geometryFunctions.h>
#include <x-poly/utilities/convexHull.h>
#include <x-poly/utilities/utilities.h>

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
public:
    Polygon(std::vector<int>& points, std::vector<Point>& p);
    Polygon(std::vector<Point>& p);

    double getDiameter();
    double getArea();
    Point getCentroid();

    void mutate(std::vector<Point>& p);
    void getSegments(std::vector<Segment>& segments);
    void getSegments(std::vector<Segment>& segments, int offset);
    bool containsPoint(std::vector<Point>& p, Point point);
    bool inEdges(std::vector<Point>& p, Point point);
    double signedArea(std::vector<Point>& p);

    bool isConvex(std::vector<Point>& p);
    bool isClockwise(std::vector<Point>& p);
    std::vector<int> getPoints() const;
    int numberOfSides();

    bool operator==(const Polygon& other) const;
    std::string getString();
};

#endif