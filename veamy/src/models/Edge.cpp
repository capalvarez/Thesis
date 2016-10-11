#include <veamy/models/Edge.h>

Edge::Edge(int p1, int p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Pair<double> Edge::getNormal(std::vector<int> indexes, std::vector<Point> points) {
    Point P1 = points[p1];
    Point P2 = points[p2];

    return Pair<double>((P2.getY()-P1.getY()), -(P2.getX()-P1.getX()));
}

double Edge::getLength(std::vector<Point> points) {
    Point P1 = points[p1];
    Point P2 = points[p2];

    return sqrt(pow(P1.getX() - P2.getX(),2) + pow(P1.getY() - P2.getY(), 2));
}

std::vector<int> Edge::getDOFsInside(int k, int numberSides) {
    std::vector<int> points;

    points.push_back(2*p1);
    points.push_back(2*p1+1);

    for(int i=0; i<(k-1); i++){
        points.push_back(2*(numberSides + p1*(k-1) + i));
        points.push_back(2*(numberSides + p1*(k-1) + i) + 1);
    }

    points.push_back(2*p2);
    points.push_back(2*p2+1);

    return points;
}



