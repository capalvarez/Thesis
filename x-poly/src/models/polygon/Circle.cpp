#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/models/polygon/Circle.h>

Circle::Circle(double r, Point c) {
    this->radius = r;
    this->center = c;
}

std::vector<Point> Circle::discretizeCircle(int grade) {
    std::vector<Point> points;
    double delta = 360 / grade;

    double angle = 0;
    while (angle < 360) {
        double x = center.getX() + radius * cos(xpoly_utilities::radian(angle));
        double y = center.getY() + radius * sin(xpoly_utilities::radian(angle));

        points.push_back(Point(x, y));

        angle += delta;
    }

    return points;
}
