#include <x-poly/models/PolygonalMesh.h>
#include <float.h>

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
    int j;

    return this->findContainerPolygon(p, i, j);
}

int PolygonalMesh::findContainerPolygon(Point p, int &last) {
    int i = utilities::random_integer(0,this->polygons.size()-1);

    return this->findContainerPolygon(p, i, last);
}

int PolygonalMesh::findContainerPolygon(Point p, int i, int &last) {
    while(true){
        bool found = false;
        Polygon poly = this->polygons[i];

        if(poly.containsPoint(this->points.getList(), p)){
            return i;
        }else {
            PointSegment lookup(poly.getCentroid(), p);
            NeighbourInfo neighbour = getNeighbour(i,lookup);

            if(neighbour.neighbour>-1) {
                i = neighbour.neighbour;
                found = true;
            }
        }

        if (!found) {
            last = i;
            return -1;
        }
    }
}

void PolygonalMesh::update() {
    std::vector<Point> p = this->points.getList();

    for (int i = 0; i < this->polygons.size(); ++i) {
        polygons[i].update(p);
    }
}

void PolygonalMesh::deformPoint(int point_index, double dX, double dY) {
    this->points[point_index].deform(dX, dY);
}

Polygon& PolygonalMesh::getPolygon(int index) {
    return this->polygons[index];
}

NeighbourInfo PolygonalMesh::getNeighbour(int poly_index, PointSegment direction) {
    std::vector<int> p;
    return getNeighbour(poly_index, direction, p);
}

NeighbourInfo PolygonalMesh::getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous) {
    Polygon& poly = getPolygon(poly_index);

    std::vector<IndexSegment> polySeg;
    poly.getSegments(polySeg);

    for (int j = 0; j < polySeg.size() ; ++j) {
        Point p;
        bool intersects = polySeg[j].intersection(this->points.getList(), direction, p);

        Neighbours edge = this->edges.get(polySeg[j]);

        int next_poly = edge.getFirst()!=poly_index? edge.getFirst() : edge.getSecond();
        auto find = std::find(previous.begin(), previous.end(), next_poly);
        if(next_poly==-1 || find!=previous.end()){
            continue;
        }

        // Special case: Intersection through vertex
        int vertexIndex;
        if(poly.isVertex(p, this->points.getList(), vertexIndex)){
            previous.clear();

            UniqueList<int> neighbours;
            this->getDirectNeighbours(poly_index, neighbours);
            int neighbour = getNeighbourFromCommonVertexSet(direction, neighbours.getList(), vertexIndex, previous);

            NeighbourInfo n(neighbour, polySeg[j], p, false);
            n.isVertex = true;

            return n;
        }

        if(intersects && !polySeg[j].isContained(direction, this->points.getList())){
            if(find == previous.end()) {
                int vertexIndex;

                if(polySeg[j].isInCorner(p, this->points.getList(), vertexIndex)){
                    Polygon nextPoly = getPolygon(next_poly);
                    std::vector<IndexSegment> candidateSegments = nextPoly.getAdjacentEdges(vertexIndex);

                    bool isInEdge = candidateSegments[0].isContained(direction, this->points.getList()) ||
                                    candidateSegments[1].isContained(direction, this->points.getList());

                    return NeighbourInfo(next_poly, polySeg[j], p, isInEdge);
                }

                return NeighbourInfo(next_poly, polySeg[j], p, false);
            }
        }
    }

    return NeighbourInfo(-1,IndexSegment(),Point(), false);
}

int PolygonalMesh::getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, int vertexIndex,
                                                   std::vector<int> &previousPolygons) {
    double diff = DBL_MAX;
    int neighbour = 0;

    double tolerance = XPolyConfig::instance()->getTolerance();
    Pair<double> slopeDirection = direction.getSlope();

    for (int i = 0; i < vertexSet.size(); ++i) {
        if(!getPolygon(vertexSet[i]).isVertex(vertexIndex)){
            continue;
        }

        previousPolygons.push_back(vertexSet[i]);
        Pair<double> slopeNeighbour = PointSegment(getPoint(vertexIndex), getPolygon(vertexSet[i]).getCentroid()).getSlope();

        if(std::abs(slopeNeighbour.first)<tolerance && std::abs(slopeDirection.first)<tolerance){

        }else{
            double sD = slopeDirection.second/slopeDirection.first;
            double sN = slopeNeighbour.second/slopeNeighbour.first;

            double newDiff = std::abs(sD-sN);

            if(newDiff < diff && sD*sN>0){
                diff = newDiff;
                neighbour = vertexSet[i];
            }
        }
    }
    return neighbour;
}

Region PolygonalMesh::getRegion() const{
    return this->region;
}

bool PolygonalMesh::areNeighbours(int poly1, int poly2) {
    return areNeighbours(polygons[poly1], poly2);
}

bool PolygonalMesh::areNeighbours(Polygon poly1, int poly2) {
    std::vector<IndexSegment> poly1_segments;
    poly1.getSegments(poly1_segments);

    for(IndexSegment s: poly1_segments){
        Neighbours n = edges.get(s);
        if(n.isNeighbour(poly2)){
            return true;
        }
    }

    return false;
}

void PolygonalMesh::writeElements(std::ofstream &file) {
    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }
}

void PolygonalMesh::getAllNeighbours(int poly, UniqueList<int> &neighbours) {
    std::vector<IndexSegment> poly_segs;
    this->getPolygon(poly).getSegments(poly_segs);

    for (IndexSegment s: poly_segs){
        Neighbours n = edges.get(s);
        int neighbour = n.getOther(poly);
        if(neighbour!=-1){
            neighbours.push_back(neighbour);
        }
    }
}

bool PolygonalMesh::polygonsTouch(int poly1, int poly2) {
    Polygon p1 = this->getPolygon(poly1);
    Polygon p2 = this->getPolygon(poly2);
    std::vector<int> poly2_points = p2.getPoints();

    for (int i = 0; i < poly2_points.size(); ++i) {
        if(p1.isVertex(poly2_points[i])){
            return true;
        }
    }

    return false;
}

bool PolygonalMesh::isInDomain(Point p) {
    return this->region.containsPoint(p);
}

bool PolygonalMesh::isInBorder(Point p) {
    return this->region.inEdges(p);
}

void PolygonalMesh::getDirectNeighbours(int poly, UniqueList<int> &neighbours) {
    this->getAllNeighbours(poly, neighbours);
    UniqueList<int> neighbours_neighbours;

    for (int i = 0; i < neighbours.size(); ++i) {
        this->getAllNeighbours(neighbours[i], neighbours_neighbours);
    }

    for (int j = 0; j < neighbours_neighbours.size(); ++j) {
        int candidate = neighbours_neighbours[j];
        if(!neighbours.contains(candidate) && this->polygonsTouch(poly, candidate)){
            neighbours.push_back(neighbours_neighbours[j]);
        }
    }
}
