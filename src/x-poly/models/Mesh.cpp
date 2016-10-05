#include <fstream>
#include "Mesh.h"

Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, std::vector<Segment<int>>& s) {
    this->points.assign(p.begin(), p.end());
    this->elements.assign(e.begin(), e.end());
    this->edges.assign(s.begin(), s.end());
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

std::vector<Point> Mesh::getPoints() {
    return this->points;
}

std::vector<Segment<int>> Mesh::getEdges() {
    return this->edges;
}

std::vector<Polygon> Mesh::getElements() {
    return this->elements;
}

void Mesh::printInFile(std::string fileName) {
    std::string path(getenv("HOME"));
    path += "/" + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    file << this->points.size() << std::endl;
    for(int i=0;i<this->points.size();i++){
        file << this->points[i].getString() << std::endl;
    }


    file << this->edges.size() << std::endl;
    for(int i=0;i<this->edges.size();i++){
        file << this->edges[i].getString() << std::endl;
    }

    file << this->elements.size() << std::endl;
    for(int i=0;i<this->elements.size();i++){
        file << this->elements[i].getString() << std::endl;
    }

    file.close();
}

void Mesh::breakPolygons(Segment<int> s) {

}

void Mesh::breakPolygons(Segment<Point> s) {

}

