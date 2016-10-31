#include <fracture/geometry/generator/RosetteGroupGenerator.h>


RosetteGroupGenerator::RosetteGroupGenerator(Point c, double outer, double angle) {
    this->center = c;
    this->innerRadius = outer/4;
    this->outerRadius = outer;
    this->angle = angle;
}

std::vector<Point> RosetteGroupGenerator::getPoints(double initAngle) {
    this->points.push_back(this->center);

    double angle = this->angle;

    this->generatePoint(angle/4 + initAngle, this->innerRadius);
    this->generatePoint(angle/4 + initAngle, this->outerRadius);

    this->generatePoint(-angle/4 + initAngle, this->innerRadius);
    this->generatePoint(-angle/4 + initAngle, this->outerRadius);

    this->generatePoint(angle/2 + initAngle, this->outerRadius);

    while(angle<360){
        this->generatePoint(angle + initAngle, this->innerRadius);
        this->generatePoint(angle + initAngle, this->outerRadius);
        this->generatePoint(angle + this->angle/2, this->outerRadius);

        angle+=this->angle;
    }

    return this->points;
}

void RosetteGroupGenerator::generatePoint(double angle, double radius) {
    double x = center.getX() - radius*std::cos(utilities::radian(angle));
    double y = center.getY() + radius*innerRadius*std::sin(utilities::radian(angle));

    Point point (x, y);
    this->points.push_back(point);
}
