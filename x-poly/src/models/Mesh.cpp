#include <fstream>
#include <x-poly/models/Mesh.h>


Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s, Region r) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
    this->region = r;
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

Mesh::Mesh(const Mesh &m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
    this->region = m.region;
}

List<Point>& Mesh::getPoints() {
    return this->points;
}

std::vector<Polygon>& Mesh::getPolygons() {
    return this->polygons;
}

SegmentMap &Mesh::getSegments() {
    return this->edges;
}

List<Point> Mesh::getPoints() const {
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
        file << this->points.get(i).getString() << std::endl;
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

    return this->findContainerPolygon(p, i);
}

int Mesh::findContainerPolygon(Point p, int i) {
    while(true){
        bool found = false;
        Polygon poly = this->polygons[i];

        if(poly.containsPoint(this->points.getList(), p)){
            return i;
        }else {
            Segment<Point> lookup(poly.getCentroid(), p);
            NeighbourInfo neighbour = getNeighbour(i,lookup);

            if(neighbour.neighbour>-1) {
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

    if(container.inEdges(this->points.getList(), p)){
        Segment<int> containerEdge = container.containerEdge(this->points.getList(), p);

        return containerEdge.isBoundary(this->points.getList());
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
        bool intersects = polySeg[j].intersection(this->points.getList(), direction, p);

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

Region Mesh::getRegion() const{
    return this->region;
}
