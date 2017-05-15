#include <fracture/geometry/generator/QuarterPointElementsGenerator.h>
#include <fracture/config/FractureConfig.h>

QuarterPointElementsGenerator::QuarterPointElementsGenerator(Point c, double angle, double radius) {
    this->center = c;
    this->angle = angle;
    this->innerRadius = radius/4;
    this->outerRadius = radius;
}

std::vector<Point> QuarterPointElementsGenerator::generateGroup(double initAngle) {
    std::vector<Point> onSegment;
    this->points.push_back(this->center);

    double startAngle = initAngle + 180;
    double angle = this->angle;

    int p1 = this->generatePoint(angle + startAngle, this->innerRadius);
    int p2 = this->generatePoint(angle + startAngle, this->outerRadius);
    int p3 = this->generatePoint(angle + this->angle / 2 + startAngle, this->outerRadius);

    borderPointIndexes.push_back(p1);
    borderPointIndexes.push_back(p3);

    while(angle<360){
        std::vector<int> quarterPointPoints = {0, p1, p2, p3};

        p1 = this->generatePoint(angle + startAngle, this->innerRadius);
        p2 = this->generatePoint(angle + startAngle, this->outerRadius);
        p3 = this->generatePoint(angle + this->angle / 2 + startAngle, this->outerRadius);

        quarterPointPoints.push_back(p2);
        quarterPointPoints.push_back(p1);

        elements.push_back(Polygon(quarterPointPoints, this->getPoints()));
        borderPointIndexes.push_back(p2);
        borderPointIndexes.push_back(p3);

        angle+=this->angle;
    }

    std::vector<int> quarterPointPoints = {0, p1, p2, p3};

    p1 = this->generatePoint(angle + startAngle, this->innerRadius);
    p2 = this->generatePoint(angle + startAngle, this->outerRadius);

    borderPointIndexes.push_back(p2);
    borderPointIndexes.push_back(p3);

    elements.push_back(Polygon(quarterPointPoints, this->getPoints()));
    borderPointIndexes.push_back(p2);

    return onSegment;
}

int QuarterPointElementsGenerator::generatePoint(double angle, double radius) {
    double x = center.getX() + radius*std::cos(utilities::radian(angle));
    double y = center.getY() + radius*std::sin(utilities::radian(angle));

    Point point (x, y);

    this->points.push_back(point);

    return this->points.size() - 1;
}

std::vector<Point> QuarterPointElementsGenerator::getPoints() {
    return this->points;
}
