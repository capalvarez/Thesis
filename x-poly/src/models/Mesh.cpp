#include <fstream>
#include <x-poly/models/Mesh.h>


Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s) {
    this->points.assign(p.begin(), p.end());
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

std::vector<Point>& Mesh::getPoints() {
    return this->points;
}

std::vector<Polygon>& Mesh::getPolygons() {
    return this->polygons;
}

SegmentMap &Mesh::getSegments() {
    return this->edges;
}

std::vector<Point> Mesh::getPoints() const {
    return this->points;
}

std::vector<Polygon> Mesh::getPolygons() const {
    return this->polygons;
}

SegmentMap Mesh::getSegments() const {
    return this->edges;
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
    for(auto e: this->edges.getMap()){
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
    int i = utilities::random_integer(0,this->polygons.size()-1);

    while(true){
        bool found = false;
        Polygon poly = this->polygons[i];

        if(poly.containsPoint(this->points, p)){
            return i;
        }else {
            Segment<Point> lookup(poly.getCentroid(), p);
            NeighbourInfo neighbour = getNeighbour(i,lookup);

            if(neighbour.neighbour!=-1) {
                i = neighbour.neighbour;
                found = true;
            }
        }

        if (!found) {
            return -1;
        }
    }
}

bool Mesh::isInBoundary(Point p) {
    Polygon& container = this->polygons[findContainerPolygon(p)];

    if(container.inEdges(this->points, p)){
        Segment<int> containerEdge = container.containerEdge(this->points, p);

        return containerEdge.isBoundary(this->points);
    }

    return false;
}

Polygon& Mesh::getPolygon(int index) {
    return this->polygons[index];
}

NeighbourInfo Mesh::getNeighbour(int poly_index, Segment<Point> direction) {
    return getNeighbour(poly_index, direction, -1);
}

NeighbourInfo Mesh::getNeighbour(int poly_index, Segment<Point> direction, int previous) {
    Polygon& poly = getPolygon(poly_index);

    std::vector<Segment<int>> polySeg;
    poly.getSegments(polySeg);

    for (int j = 0; j < polySeg.size() ; ++j) {
        Point p;
        bool intersects = polySeg[j].intersection(this->points, direction, p);

        if(intersects){
            Neighbours edge = this->edges.get(polySeg[j]);

            int next_poly = edge.getFirst()!=poly_index? edge.getFirst() : edge.getSecond();

            if(next_poly!=previous) {
                return NeighbourInfo(next_poly, polySeg[j], p);
            }
        }
    }

    return NeighbourInfo(-1,Segment<int>(),Point());
}

bool Mesh::isFull() {
    return this->points.size()>0;
}
