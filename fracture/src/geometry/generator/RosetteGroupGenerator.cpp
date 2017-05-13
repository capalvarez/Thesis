#include <fracture/geometry/generator/RosetteGroupGenerator.h>
#include <fracture/config/FractureConfig.h>

RosetteGroupGenerator::RosetteGroupGenerator(Point c, double angle, double radius) {
    this->center = c;
    this->angle = angle;
    this->innerRadius = radius/4;
    this->outerRadius = radius;
}

std::vector<Point> RosetteGroupGenerator::generatePoints(double initAngle) {
    std::vector<Point> onSegment;
    this->points.push_back(this->center);

    double startAngle = initAngle + 180;
    double angle = this->angle;

    this->generatePoint(angle / 4 + startAngle, this->innerRadius);
    this->generatePoint(angle / 4 + startAngle, this->outerRadius);

    this->generatePoint(-angle / 4 + startAngle, this->innerRadius);
    this->generatePoint(-angle / 4 + startAngle, this->outerRadius);

    this->generatePoint(angle / 2 + startAngle, this->outerRadius);

    while(angle<360){
        this->generatePoint(angle + startAngle, this->innerRadius);
        this->generatePoint(angle + startAngle, this->outerRadius);
        this->generatePoint(angle + this->angle / 2 + startAngle, this->outerRadius);

        if(std::abs(angle-180)<FractureConfig::instance()->getTolerance()){
            onSegment.push_back(this->points[this->points.size()-2]);
            onSegment.push_back(this->points[this->points.size()-3]);
        }

        angle+=this->angle;
    }

    return onSegment;
}

void RosetteGroupGenerator::generatePoint(double angle, double radius) {
    double x = center.getX() + radius*std::cos(utilities::radian(angle));
    double y = center.getY() + radius*std::sin(utilities::radian(angle));

    Point point (x, y);

    this->points.push_back(point);
}

std::vector<Point> RosetteGroupGenerator::getPoints() {
    return this->points;
}
