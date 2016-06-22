#ifndef THESIS_POLYGON_H
#define THESIS_POLYGON_H

#include <vector>
#include "models/basic/Point.h"
#include "models/basic/Segment.h"
#include <utilities/geometryFunctions.h>
#include <utilities/convexHull.h>
#include <utilities/utilities.h>

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

    void getSegments(std::vector<Segment>& segments);
    bool containsPoint(std::vector<Point>& p, Point point);
    bool inEdges(std::vector<Point>& p, Point point);
    double signedArea(std::vector<Point>& p);

    bool isConvex(std::vector<Point>& p);
};

#endif