#include <include/x-poly/models/Triangulation.h>
#include <cstdlib>

Triangulation::Triangulation(std::vector <Point> p, std::vector <Triangle> t, SegmentMap edges) {
    this->points.assign(p.begin(),p.end());
    this->triangles.assign(t.begin(),t.end());
    this->edgeMap = edges;
}

void Triangulation::writeInFile(std::string fileName) {
    std::string path = string_utils::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    file << this->points.size() << std::endl;
    for(int i=0;i<this->points.size();i++){
        file << this->points[i].getString() << std::endl;
    }

    file << this->triangles.size() << std::endl;
    for(int i=0;i<this->triangles.size();i++){
        file << this->triangles[i].getString() << std::endl;
    }

    file.close();
}

std::vector<Point> Triangulation::getPoints() {
    return this->points;
}

SegmentMap Triangulation::getSegments() {
    return this->edgeMap;
}
