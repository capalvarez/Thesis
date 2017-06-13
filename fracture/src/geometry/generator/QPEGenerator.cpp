#include <fracture/geometry/generator/QPEGenerator.h>
#include <fracture/config/FractureConfig.h>

QPEGenerator::QPEGenerator(Point c, double angle, double radius) {
    this->center = c;
    this->angle = angle;
    this->innerRadius = radius/4;
    this->outerRadius = radius;
}

void QPEGenerator::generateGroup(double initAngle) {
    this->points.push_back(this->center);

    double startAngle = initAngle + 180;
    double angle = this->angle;

    int p1 = this->generatePoint(startAngle, this->innerRadius);
    int p2 = this->generatePoint(startAngle, this->outerRadius);
    int p3 = this->generatePoint(this->angle / 2 + startAngle, this->outerRadius);

    borderPoints.insert(borderPoints.begin(), p3);

    while(angle<360){
        std::vector<int> quarterPointPoints = {0, p1, p2, p3};

        p1 = this->generatePoint(angle + startAngle, this->innerRadius);
        p2 = this->generatePoint(angle + startAngle, this->outerRadius);
        p3 = this->generatePoint(angle + this->angle / 2 + startAngle, this->outerRadius);

        quarterPointPoints.push_back(p2);
        quarterPointPoints.push_back(p1);

        elements.push_back(Polygon(quarterPointPoints, this->points));
        borderPoints.insert(borderPoints.begin(), p2);
        borderPoints.insert(borderPoints.begin(), p3);

        angle+=this->angle;
    }

    std::vector<int> quarterPointPoints = {0, p1, p2, p3};

    p1 = this->generatePoint(angle + startAngle, this->innerRadius);
    p2 = this->generatePoint(angle + startAngle, this->outerRadius);

    quarterPointPoints.push_back(p2);
    quarterPointPoints.push_back(p1);
    elements.push_back(Polygon(quarterPointPoints, this->points));
}

int QPEGenerator::generatePoint(double angle, double radius) {
    double x = center.getX() + radius*std::cos(utilities::radian(angle));
    double y = center.getY() + radius*std::sin(utilities::radian(angle));

    Point point (x, y);

    this->points.push_back(point);

    return this->points.size() - 1;
}

std::vector<Point> QPEGenerator:: getPoints() {
    return this->points;
}

std::vector<int> QPEGenerator::getBorderPoints() {
    return this->borderPoints;
}

std::vector<Polygon> QPEGenerator::getElements() {
    return this->elements;
}
