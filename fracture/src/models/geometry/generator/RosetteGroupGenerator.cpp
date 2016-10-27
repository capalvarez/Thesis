#include <fracture/models/geometry/generator/RosetteGroupGenerator.h>


RosetteGroupGenerator::RosetteGroupGenerator(Point c, double outer, double angle) {
    this->center = c;
    this->innerRadius = outer/4;
    this->outerRadius = outer;
    this->angle = angle;
}

std::vector<Point> RosetteGroupGenerator::getPoints(double initAngle) {
    this->points.push_back(this->center);

    double angle = this->angle;

    double innerX = center.getX() - this->innerRadius*std::cos(utilities::radian(angle/4 + initAngle));
    double innerY = center.getY() + this->innerRadius*std::sin(utilities::radian(angle/4 + initAngle));

    double outerX = center.getX() - this->outerRadius*std::cos(utilities::radian(angle/4 + initAngle));
    double outerY = center.getY() + this->outerRadius*std::sin(utilities::radian(angle/4 + initAngle));

    double outerX2 = center.getX() - this->outerRadius*std::cos(utilities::radian(angle/2 + initAngle));
    double outerY2 = center.getY() + this->outerRadius*std::sin(utilities::radian(angle/2 + initAngle));

    Point inner (innerX, innerY);
    Point outer (outerX, outerY);
    Point outer2 (outerX2, outerY2);

    this->points.push_back(inner);
    this->points.push_back(outer);


    innerX = center.getX() - this->innerRadius*std::cos(utilities::radian(-angle/4 + initAngle));
    innerY = center.getY() + this->innerRadius*std::sin(utilities::radian(-angle/4 + initAngle));

    outerX = center.getX() - this->outerRadius*std::cos(utilities::radian(-angle/4 + initAngle));
    outerY = center.getY() + this->outerRadius*std::sin(utilities::radian(-angle/4 + initAngle));

    inner = Point(innerX, innerY);
    outer = Point(outerX, outerY);

    this->points.push_back(inner);
    this->points.push_back(outer);
    this->points.push_back(outer2);


    while(angle<360){
        innerX = center.getX() - this->innerRadius*std::cos(utilities::radian(angle + initAngle));
        innerY = center.getY() + this->innerRadius*std::sin(utilities::radian(angle + initAngle));

        outerX = center.getX() - this->outerRadius*std::cos(utilities::radian(angle + initAngle));
        outerY = center.getY() + this->outerRadius*std::sin(utilities::radian(angle + initAngle));

        outerX2 = center.getX() - this->outerRadius*std::cos(utilities::radian(angle + this->angle/2 + initAngle));
        outerY2 = center.getY() + this->outerRadius*std::sin(utilities::radian(angle + this->angle/2 + initAngle));

        Point inner (innerX, innerY);
        Point outer (outerX, outerY);
        Point outer2 (outerX2, outerY2);

        this->points.push_back(inner);
        this->points.push_back(outer);
        this->points.push_back(outer2);

        angle+=this->angle;
    }

    return this->points;
}
