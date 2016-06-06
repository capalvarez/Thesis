#include <vector>
#include "Point.h"
#include "Segment.h"

class Polygon {
protected:
    std::vector<int> points;
private:
    double diameter;
    double area;
    Point centroid;
    bool convex;

    double signedArea(std::vector<Point> p);
    double calculateDiameter(std::vector<Point> p);
    double calculateArea(std::vector<Point> p);
    Point calculateCentroid(std::vector<Point> p);
    bool inEdges(std::vector<Point> p, Point point);
public:
    Polygon(std::vector<int> points, std::vector<Point> p);
    ~Polygon();

    double getDiameter();
    double getArea();
    Point getCentroid();

    void getSegments(std::vector<Segment> segments);
    bool containsPoint(std::vector<Point> p, Point point);

    bool isConvex(std::vector<Point> p);
};

