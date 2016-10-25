#include <fracture/models/geometry/generator/RosetteGroupGenerator.h>


RosetteGroupGenerator::RosetteGroupGenerator(Point c, double inner, double outer, double angle) {
    this->center = c;
    this->innerRadius = inner;
    this->outerRadius = outer;
    this->angle = angle;
}

std::vector<Point> RosetteGroupGenerator::getPoints() {
    this->points.push_back(this->center);

    double angle = this->angle/2;

    while(angle<=360){
        double innerX = center.getX() - this->innerRadius*std::cos(utilities::radian(angle));
        double innerY = center.getY() + this->innerRadius*std::sin(utilities::radian(angle));

        double outerX = center.getX() - this->outerRadius*std::cos(utilities::radian(angle));
        double outerY = center.getY() + this->outerRadius*std::sin(utilities::radian(angle));

        Point inner (innerX, innerY);
        Point outer (outerX, outerY);

        this->points.push_back(inner);
        this->points.push_back(outer);

        angle+=this->angle;
    }

    return this->points;
}
