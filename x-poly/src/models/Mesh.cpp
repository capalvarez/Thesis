#include <x-poly/models/Mesh.h>

void Mesh::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    file << this->points.size() << std::endl;
    for(int i=0;i<this->points.size();i++){
        file << this->points[i].getString() << std::endl;
    }

    file << this->edges.size() << std::endl;
    for(auto e: this->edges.getMap()){
        IndexSegment edge = e.first;
        file << edge.getString() << std::endl;
    }

    writeElements(file);

    file.close();
}

SegmentMap &Mesh::getSegments() {
    return this->edges;
}

SegmentMap Mesh::getSegments() const {
    return this->edges;
}

UniqueList <Point> &Mesh::getPoints() {
    return this->points;
}

UniqueList <Point> Mesh::getPoints() const {
    return this->points;
}

bool Mesh::isFull() {
    return this->points.size()>0;
}
