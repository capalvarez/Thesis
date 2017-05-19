#include <fracture/geometry/BreakableMesh.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>
#include <fracture/utilities/fractureutilities.h>

struct greater{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(const PolygonalMesh& m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
    this->region = m.getRegion();
}

PolygonChangeData
BreakableMesh::breakMesh(int init, PointSegment crack, bool initialCrackTip, UniqueList<Pair<int>> &newPoints) {
    return breakMesh(init, crack, initialCrackTip, newPoints, std::vector<int>());
}

PolygonChangeData
BreakableMesh::breakMesh(int init, PointSegment crack, bool initialCrackTip, UniqueList<Pair<int>> &newPoints,
                         std::vector<int> previous) {
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;

    NeighbourInfo n1 = getNeighbour(init, crack, previous);

    if(n1.neighbour<0){
        //If the crack is in one element, return the same element
        return PolygonChangeData(oldPolygons, newPolygons, init);
    }

    int last = -1;
    if(initialCrackTip){
        IndexSegment container_edge = this->getPolygon(init).containerEdge(getPoints().getList(), crack.getFirst());
        NeighbourInfo n0 = NeighbourInfo(init, container_edge,crack.getFirst() ,false);
        n0.isVertex = container_edge.isEndPoint(crack.getFirst(), this->points.getList());

        breakPolygons(n0, n1, -1, oldPolygons, newPolygons,
                      newPoints);
        last = this->polygons.size() - 1;
    }


    bool oneLastIteration = false;

    while(true){
        Polygon& poly1 = getPolygon(n1.neighbour);

        if(poly1.containsPoint(this->points.getList(), crack.getSecond())){
            if(poly1.inEdges(this->points.getList(), crack.getSecond())){
                if(!oneLastIteration){
                    oneLastIteration = true;
                }
            }else{
                return PolygonChangeData(oldPolygons, newPolygons, n1.neighbour);
            }
        }

        std::vector<int> poly1_points = poly1.getPoints();

        if(!n1.isVertex){
            previous = {init, last};
        }else{
            previous.push_back(last);
        }

        NeighbourInfo n2 = getNeighbour(n1.neighbour, crack, previous);

        if(n1.isEdge){
            init = n1.neighbour;
            n1 = n2;

            continue;
        }

        breakPolygons(n1, n2, init, oldPolygons, newPolygons,
                      newPoints);
        this->printInFile("meshmesh.txt");
        this->edges.printInFile("edges.txt");

        // Iterate
        if(oneLastIteration){
            return PolygonChangeData(oldPolygons, newPolygons, n1.neighbour);
        }

        last = this->polygons.size()-1;
        init = n1.neighbour;
        n1 = n2;
    }

}

void BreakableMesh::swapPolygons(int first, int last, std::unordered_map<IndexSegment,int,SegmentHasher> &toIgnore) {
    Polygon p1 = getPolygon(first);
    Polygon p2 = getPolygon(last);

    std::vector<IndexSegment> firstSegments;
    p1.getSegments(firstSegments);

    std::vector<IndexSegment> lastSegments;
    p2.getSegments(lastSegments);

    for(IndexSegment s: firstSegments){
        auto got = toIgnore.find(s);

        if(got==toIgnore.end()){
            edges.get(s).changeNeighbour(first, last);
        }
    }

    for(IndexSegment s: lastSegments) {
        auto got = toIgnore.find(s);

        if (got == toIgnore.end()) {
            edges.get(s).changeNeighbour(last, first);
        }
    }

    this->polygons[first] = p2;
    this->polygons[last] = p1;
}

void BreakableMesh::mergePolygons(int i1, int i2) {
    Polygon p = getPolygon(i1);

    if(!areNeighbours(i1,i2)){
        return;
    }

    std::unordered_map<IndexSegment, int, SegmentHasher> toIgnore;
    swapPolygons(i2, this->polygons.size() - 1, toIgnore);

    Polygon poly1 = getPolygon(i1);
    Polygon poly2 = getPolygon(this->polygons.size() - 1);

    SimplePolygonMerger merger;

    Polygon merged =  merger.mergePolygons(poly1, poly2, points.getList());
    this->polygons[i1] = merged;

    std::vector<IndexSegment> poly2Segments;
    poly2.getSegments(poly2Segments);

    std::unordered_map<Neighbours, int, NeighboursHasher> map;
    Neighbours n(i2, i1);
    map[n] = 0;

    for(IndexSegment s: poly2Segments){
        edges.replace_or_delete(s, this->polygons.size() - 1, i2, i1, map, toIgnore);
    }

    this->polygons.pop_back();
}

int BreakableMesh::mergePolygons(std::vector<int> &polys) {
    if(polys.size()==1){
        return polys[0];
    }

    SimplePolygonMerger merger;

    Polygon merged =  merger.mergePolygons(polys, points.getList(), *this);
    std::sort(polys.begin(), polys.end(), greater());
    this->polygons[polys.back()] = merged;

    std::unordered_map<Neighbours,int,NeighboursHasher> map;
    std::unordered_map<IndexSegment, int,SegmentHasher> toIgnore;
    std::vector<Pair<int>> pairs;
    fracture_utilities::allPairs(pairs, polys);

    for (Pair<int> p : pairs){
        Neighbours n (p);
        map[n] = 0;
    }

    for (int i = 0; i < polys.size()-1; ++i) {
        int i2 = polys[i];

        swapPolygons(i2, this->polygons.size() - 1, toIgnore);
        Polygon poly2 = getPolygon(this->polygons.size() - 1);

        std::vector<IndexSegment> poly2Segments;
        poly2.getSegments(poly2Segments);

        for(IndexSegment s: poly2Segments){
            edges.replace_or_delete(s, this->polygons.size() - 1, i2, polys.back(), map, toIgnore);
        }

        this->polygons.pop_back();
    }

    return polys.back();
}


void BreakableMesh::breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init, std::vector<Polygon> &oldPolygons,
                                  std::vector<Polygon> &newPolygons, UniqueList<Pair<int>> &newPoints) {
    Polygon& poly1 = getPolygon(n1.neighbour);
    oldPolygons.push_back(poly1);

    //Include new points on the mesh
    int p1 = this->points.push_back(n1.intersection);
    int p2 = this->points.push_back(n2.intersection);

    int p3;
    if(n1.extraPoint<0){
        p3 = this->points.force_push_back(n1.intersection);
    } else{
        p3 = n1.extraPoint;
    }

    int p4 = this->points.force_push_back(n2.intersection);

    Pair<int> entryPair = Pair<int>(p1, p3);
    Pair<int> exitPair = Pair<int>(p2, p4);

    newPoints.push_back(entryPair);
    newPoints.push_back(exitPair);

    //Split the old polygon and generate new ones
    std::vector<int> new1 = {p1, p2};
    std::vector<int> new2 = {p4, p3};

    Pair<int> pairs = computeNewPolygons(n1, n2, poly1, newPolygons,
                                         new1, new2, p1, p2, init, p3, p4);

    if(init>=0){
        this->getPolygon(init).insertOnSegment(n1.edge, {p3, p1});
        edges.insert(IndexSegment(p1,p3), init);
    }

    this->getPolygon(n2.neighbour).insertOnSegment(n2.edge, {p2, p4});
    edges.insert(IndexSegment(p2,p4), n2.neighbour);

    // Get the edge information for the old polygon and update it
    if(!n1.isVertex){
        this->edges.delete_element(n1.edge);
        if(n1.extraPoint>=0){
            this->edges.delete_element(IndexSegment(p1,p3));
        }
    }
    if(!n2.isVertex){
        this->edges.delete_element(n2.edge);
    }

    std::vector<IndexSegment> segments1;
    std::vector<IndexSegment> segments2;

    this->getPolygon(pairs.first).getSegments(segments1);
    this->getPolygon(pairs.second).getSegments(segments2);

    this->edges.insert(IndexSegment(p1,p2),Neighbours(pairs.first,-1));
    this->edges.insert(IndexSegment(p3,p4),Neighbours(n1.neighbour,-1));

    for (int i = 0; i < segments1.size() ; ++i) {
        this->edges.replace_neighbour(segments1[i], n1.neighbour, pairs.first);
    }

    for (int i = 0; i < segments2.size() ; ++i) {
        this->edges.replace_neighbour(segments2[i], n1.neighbour, pairs.second);
    }

    if(!n1.isVertex){
        this->edges.insert_if_null(IndexSegment(p1, this->getPolygon(pairs.first).getVertex(n1.edge.getFirst(), n1.edge.getSecond())),init);
        this->edges.insert_if_null(IndexSegment(p3, this->getPolygon(pairs.second).getVertex(n1.edge.getFirst(), n1.edge.getSecond())), init);
    }

    if(!n2.isVertex){
        this->edges.insert_if_null(IndexSegment(p2, this->getPolygon(pairs.first).getVertex(n2.edge.getFirst(), n2.edge.getSecond())), n2.neighbour);
        this->edges.insert_if_null(IndexSegment(p4, this->getPolygon(pairs.second).getVertex(n2.edge.getFirst(), n2.edge.getSecond())), n2.neighbour);
    }

    n2.extraPoint = p4;
}

void BreakableMesh::splitPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init, std::vector<Polygon> &oldPolygons,
                                  std::vector<Polygon> &newPolygons) {
    Polygon& poly1 = getPolygon(n1.neighbour);
    std::vector<int> poly1_points = poly1.getPoints();
    oldPolygons.push_back(poly1);

    //Include new points on the mesh
    int p1 = this->points.push_back(n1.intersection);
    int p2 = this->points.push_back(n2.intersection);

    int p3 = this->points.force_push_back(n1.intersection);
    int p4 = this->points.force_push_back(n2.intersection);

    //Split the old polygon and generate new ones
    std::vector<int> new1 = {p1, p2};
    std::vector<int> new2 = {p2, p1};

    UniqueList<int> newPoints;
    Pair<int> pairs = computeNewPolygons(n1, n2, poly1, newPolygons,
                                         new1, new2, p1, p2, init, -1, -1);

    if(init>=0){
        this->getPolygon(init).insertOnSegment(n1.edge, p1);
    }

    this->getPolygon(n2.neighbour).insertOnSegment(n2.edge, p2);

    // Get the edge information for the old polygon and update it
    if(!n1.isVertex){
        this->edges.delete_element(n1.edge);
    }
    if(!n2.isVertex){
        this->edges.delete_element(n2.edge);
    }

    std::vector<IndexSegment> segments1;
    std::vector<IndexSegment> segments2;

    this->getPolygon(pairs.first).getSegments(segments1);
    this->getPolygon(pairs.second).getSegments(segments2);

    this->edges.insert(IndexSegment(p1,p2),Neighbours(n1.neighbour,n1.neighbour));

    for (int i = 0; i < segments1.size() ; ++i) {
        this->edges.replace_neighbour(segments1[i], n1.neighbour, pairs.first);
    }

    for (int i = 0; i < segments2.size() ; ++i) {
        this->edges.replace_neighbour(segments2[i], n1.neighbour, pairs.second);
    }

    if(!n1.isVertex){
        this->edges.insert_if_null(IndexSegment(p1,n1.edge.getFirst()),init);
        this->edges.insert_if_null(IndexSegment(p1,n1.edge.getSecond()), init);
    }

    if(!n2.isVertex){
        this->edges.insert_if_null(IndexSegment(p2,n2.edge.getFirst()), n2.neighbour);
        this->edges.insert_if_null(IndexSegment(p2,n2.edge.getSecond()), n2.neighbour);
    }

    n2.extraPoint = p2;
}

Pair<int> BreakableMesh::computeNewPolygons(NeighbourInfo n1, NeighbourInfo &n2, Polygon poly1, std::vector<Polygon> &newPolygons,
                                            std::vector<int> &new1, std::vector<int> &new2, int p1, int p2, int init, int p3,
                                            int p4) {
    std::vector<int> poly1_points = poly1.getPoints();

    n1.orderCCW(this->points.getList(), poly1.getCentroid());
    n2.orderCCW(this->points.getList(), poly1.getCentroid());

    int indexOfStart,point;

    if(xpoly_utilities::orientation(points[p1],points[p2],points[n2.edge.getFirst()])>=0){
        indexOfStart = utilities::indexOf(poly1_points, n2.edge.getFirst());
        point = n2.edge.getFirst();
    }else{
        indexOfStart = utilities::indexOf(poly1_points, n2.edge.getSecond());
        point = n2.edge.getSecond();
    }

    bool edgePointsPassed = false;

    while(true){
        if(n1.isVertex){
            if(point==p1){
                break;
            }
        } else{
            if(point==n1.edge.getFirst() || point==n1.edge.getSecond() || point==n1.extraPoint) {
                if (edgePointsPassed){
                    break;
                } else{
                    edgePointsPassed = true;
                }
            }
        }



        if(point!= p1 && point!=p2){
            new1.push_back(point);
        }

        point = poly1_points[(indexOfStart+1)%poly1_points.size()];

        indexOfStart++;
    }

    edgePointsPassed = false;

    while (true){
        if(n2.isVertex){
            if(point==p4 || point==p2){
                break;
            }
        }else{
            if(point==n2.edge.getFirst() || point==n2.edge.getSecond()) {
                if (edgePointsPassed){
                    break;
                } else{
                    edgePointsPassed = true;
                }
            }
        }



        if((point!=p1 && point!=p3) && (point!=p2 && point!=p4)){
            new2.push_back(point);
        }

        point = poly1_points[(indexOfStart+1)%poly1_points.size()];

        indexOfStart++;
    }

    Polygon newPolygon1 (new1, this->points.getList());
    Polygon newPolygon2 (new2, this->points.getList());

    newPolygons.push_back(newPolygon1);
    this->polygons[n1.neighbour] = newPolygon1;

    newPolygons.push_back(newPolygon2);
    this->polygons.push_back(newPolygon2);

    int new_index1 = n1.neighbour;
    int new_index2 = this->polygons.size() - 1;

    return Pair<int>(new_index1, new_index2);
}

bool BreakableMesh::areMergeable(Polygon poly1, int poly2) {
    Polygon p2 = this->getPolygon(poly2);

    std::vector<IndexSegment> poly1_segments;
    poly1.getSegments(poly1_segments);

    bool last_was_neighbour = edges.get(poly1_segments.back()).isNeighbour(poly2);
    bool exited_once = false;
    
    for(IndexSegment s: poly1_segments){
        Neighbours n = edges.get(s);
        bool areNeighbours = n.isNeighbour(poly2);
        
        if(last_was_neighbour && !areNeighbours){
            if(!exited_once){
                exited_once = true;  
            } else {
                return false;
            }
        } 
        
        if(!last_was_neighbour && !areNeighbours && p2.isVertex(s.getFirst())){
            return false;
        }
        
        last_was_neighbour = areNeighbours;
    }

    return exited_once || last_was_neighbour;
}

std::vector<int> BreakableMesh::getUnusedPoints(std::vector<int> allPoints, std::vector<int> merged) {
    for (int i : merged) {
        allPoints.erase(std::remove(allPoints.begin(), allPoints.end(), i), allPoints.end() );
    }

    return allPoints;
}

std::vector<int> BreakableMesh::getAllPoints(std::vector<int> polys) {
    UniqueList<int> all;
    for (int p : polys) {
        Polygon poly = getPolygon(p);
        all.push_list(poly.getPoints());
    }

    return all.getList();
}
