#include <veamy/matrix/quadrature/QuadraturePolygon.h>

QuadraturePolygon::QuadraturePolygon(Polygon p) {
    this->polygon = p;
}

double QuadraturePolygon::integrate(BodyForce *f, std::vector<Point> points) {
    double integral = 0;

    std::vector<int> polygonPoints = polygon.getPoints();
    int n = (int) polygonPoints.size();

    Segment<int> prev (polygonPoints[n-1], polygonPoints[0]);
    Segment<int> next (polygonPoints[0], polygonPoints[1]);

    for (int i = 0; i < n; ++i) {
        Point point = points[polygonPoints[i]];
        std::vector<Point> smallPolygon = {prev.middlePoint(points), points[polygonPoints[i]],
                                           next.middlePoint(points), polygon.getCentroid()};

        double area = geometry_functions::area(smallPolygon);

        integral += area*f->apply(point.getX(), point.getY());
    }

    return integral;
}

