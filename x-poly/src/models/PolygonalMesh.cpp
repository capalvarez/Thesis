#include <x-poly/models/PolygonalMesh.h>

PolygonalMesh::PolygonalMesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s, Region r) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
    this->region = r;
}

PolygonalMesh::PolygonalMesh() {}

PolygonalMesh::~PolygonalMesh() {}

PolygonalMesh::PolygonalMesh(const PolygonalMesh &m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
    this->region = m.region;
}

std::vector<Polygon>& PolygonalMesh::getPolygons() {
    return this->polygons;
}

std::vector<Polygon> PolygonalMesh::getPolygons() const {
    return this->polygons;
}

int PolygonalMesh::findContainerPolygon(Point p) {
    int i = utilities::random_integer(0,this->polygons.size()-1);

    return this->findContainerPolygon(p, i);
}

int PolygonalMesh::findContainerPolygon(Point p, int i) {
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

bool PolygonalMesh::isInBoundary(Point p) {
    Polygon& container = this->polygons[findContainerPolygon(p)];

    if(container.inEdges(this->points.getList(), p)){
        Segment<int> containerEdge = container.containerEdge(this->points.getList(), p);

        return containerEdge.isBoundary(this->points.getList());
    }

    return false;
}

Polygon& PolygonalMesh::getPolygon(int index) {
    return this->polygons[index];
}

NeighbourInfo PolygonalMesh::getNeighbour(int poly_index, Segment<Point> direction) {
    return getNeighbour(poly_index, direction, -1);
}

NeighbourInfo PolygonalMesh::getNeighbour(int poly_index, Segment<Point> direction, int previous) {
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

Region PolygonalMesh::getRegion() const{
    return this->region;
}

bool PolygonalMesh::areNeighbours(int poly1, int poly2) {
    return false;
}

void PolygonalMesh::writeElements(std::ofstream &file) {
    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }
}
