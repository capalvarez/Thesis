#include "Mesh.h"

Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, std::vector<Segment>& s) {
    this->points.assign(p.begin(), p.end());
    this->elements.assign(e.begin(), e.end());
    this->edges.assign(s.begin(), s.end());
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

std::vector<Point> Mesh::getPoints() {
    return this->points;
}

std::vector<Segment> Mesh::getEdges() {
    return this->edges;
}

std::vector<Polygon> Mesh::getElements() {
    return this->elements;
}







