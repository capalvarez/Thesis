#include <include/x-poly/models/Triangulation.h>
#include <cstdlib>

Triangulation::Triangulation(std::vector <Point> &p, std::vector <Triangle> &t) {
    this->points.assign(p.begin(),p.end());
    this->triangles.assign(t.begin(),t.end());
}

void Triangulation::writeInFile(std::string fileName) {
    std::string path("C:\\Users\\Catalina");
    path += "\\" + fileName;

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

