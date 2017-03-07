#include <fracture/geometry/generator/RosetteGroupGenerator.h>

RosetteGroupGenerator::RosetteGroupGenerator(Point c, double outer, double angle, int center_container,
                                             Polygon container) {
    this->center = c;
    this->innerRadius = outer/4;
    this->outerRadius = outer;
    this->angle = angle;
    this->changedPolygons.insert(center_container);
    this->currentContainer = center_container;
    this->current = container;
}

std::vector<Point> RosetteGroupGenerator::getPoints(double initAngle, BreakableMesh mesh) {
    this->points.push_back(this->center);

    double angle = this->angle;

    this->generatePoint(angle / 4 + initAngle, this->innerRadius, mesh);
    this->generatePoint(angle / 4 + initAngle, this->outerRadius, mesh);

    this->generatePoint(-angle / 4 + initAngle, this->innerRadius, mesh);
    this->generatePoint(-angle / 4 + initAngle, this->outerRadius, mesh);

    this->generatePoint(angle / 2 + initAngle, this->outerRadius, mesh);

    while(angle<360){
        this->generatePoint(angle + initAngle, this->innerRadius, mesh);
        this->generatePoint(angle + initAngle, this->outerRadius, mesh);
        this->generatePoint(angle + this->angle / 2, this->outerRadius, mesh);

        angle+=this->angle;
    }

    return this->points;
}

void RosetteGroupGenerator::generatePoint(double angle, double radius, BreakableMesh mesh) {
    double x = center.getX() - radius*std::cos(utilities::radian(angle));
    double y = center.getY() + radius*std::sin(utilities::radian(angle));

    Point point (x, y);

    if(!this->current.containsPoint(mesh.getPoints().getList(), point)){
        int newContainer = mesh.findContainerPolygon(point, this->currentContainer);

        // No polygon contains this point (it's outside the region, so it's ignored)
        if(newContainer==-1){
            return;
        }

        this->currentContainer = newContainer;
        this->current = mesh.getPolygon(newContainer);

        this->changedPolygons.insert(newContainer);
    }

    this->points.push_back(point);
}

std::set<int> RosetteGroupGenerator::getChangedPolygons() {
    return this->changedPolygons;
}
