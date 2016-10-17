#include <fstream>
#include <x-poly/models/Mesh.h>


Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, std::unordered_map<Segment<int>,Pair<int>,SegmentHasher> s) {
    this->points.assign(p.begin(), p.end());
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

std::vector<Point> Mesh::getPoints() {
    return this->points;
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
    for(auto e: this->edges){
        Segment<int> edge = e.first;
        file << edge.getString() << std::endl;
    }

    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }

    file.close();
}

int Mesh::findContainerPolygon(Point p) {
    int i = utilities::random_integer(0,this->polygons.size());

    while(true){
        bool found = false;
        Polygon poly = this->polygons[i];

        if(poly.containsPoint(this->points, p)){
            return i;
        }else{
            Segment<Point> lookup(poly.getCentroid(), p);

            std::vector<Segment<int>> polySeg;
            poly.getSegments(polySeg);

            for (int j = 0; j < polySeg.size() ; ++j) {
                if(polySeg[j].intersects(this->points, lookup)){
                    Pair<int> edge = this->edges[polySeg[j]];

                    i = edge.first!=i? i : edge.second;
                    found = true;
                    break;
                }
            }

            if(!found){
                return -1;
            }
        }
    }
}

bool Mesh::isInBoundary(Point p) {
    return false;
}


