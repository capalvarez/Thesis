#include "Mesh.h"

Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon *> &e) {
    this->points.assign(p.begin(), p.end());
    this->elements.assign(e.begin(), e.end());
}


Mesh::Mesh() {

}


Mesh::~Mesh() {
    std::for_each(elements.begin(), elements.end(), utilities::DeleteVector<Polygon*>());
}



