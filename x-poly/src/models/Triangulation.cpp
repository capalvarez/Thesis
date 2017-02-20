#include <x-poly/models/Triangulation.h>


Triangulation::Triangulation(std::vector <Point> &p, std::vector <Triangle> &t, SegmentMap edges) {
    this->points.push_list(p);
    this->triangles.assign(t.begin(),t.end());
    this->edges = edges;
}

std::vector<Triangle> Triangulation::getTriangles() {
    return this->triangles;
}

void Triangulation::writeElements(std::ofstream &file) {
    file << this->triangles.size() << std::endl;
    for(int i=0;i<this->triangles.size();i++){
        file << this->triangles[i].getString() << std::endl;
    }
    file.close();
}

