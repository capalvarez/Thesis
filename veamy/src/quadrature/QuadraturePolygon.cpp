#include <include/veamy/quadrature/QuadraturePolygon.h>

QuadraturePolygon::QuadraturePolygon(Polygon p) {
    this->polygon = p;
}

double QuadraturePolygon::integrate(BodyForce *f, std::vector<Point> points) {
    double integral = 0;

    std::vector<int> polygonPoints = polygon.getPoints();
    int n = (int) polygonPoints.size();

    IndexSegment prev;
    IndexSegment next;

    for (int i = 0; i < n; ++i) {
        prev = IndexSegment(polygonPoints[(n+i-1)%n], polygonPoints[i]);
        next = IndexSegment(polygonPoints[i], polygonPoints[(i+1)%n]);

        Point point = points[polygonPoints[i]];
        std::vector<Point> smallPolygon = {prev.middlePoint(points), points[polygonPoints[i]],
                                           next.middlePoint(points), polygon.getCentroid()};

        double area = geometry_functions::area(smallPolygon);

        integral += area*f->apply(point.getX(), point.getY());
    }

    return integral;
}

