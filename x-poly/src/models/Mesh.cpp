#include <fstream>
#include <x-poly/models/Mesh.h>


Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, std::vector<Segment<int>>& s) {
    this->points.assign(p.begin(), p.end());
    this->polygons.assign(e.begin(), e.end());
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

std::vector<Polygon> Mesh::getPolygons() {
    return this->polygons;
}

void Mesh::printInFile(std::string fileName) {
    std::string path("C:\\Users\\Catalina");
    path += "\\" + fileName;

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

    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }

    file.close();
}

