#include <fracture/geometry/BreakableMesh.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(const PolygonalMesh& m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
    this->region = m.getRegion();
}

PolygonChangeData BreakableMesh::breakMesh(int init, PointSegment crack) {
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;

    NeighbourInfo n1 = getNeighbour(init, crack);

    // TODO: Quick fix
    if(n1.neighbour<0){
        //If the crack is in one element, return the same element
        return PolygonChangeData(oldPolygons, newPolygons, init);
    }

    while(true){
        Polygon& poly1 = getPolygon(n1.neighbour);

        if(poly1.containsPoint(this->points.getList(), crack.getSecond())){
            return PolygonChangeData(oldPolygons, newPolygons, n1.neighbour);
        }

        std::vector<int> poly1_points = poly1.getPoints();
        NeighbourInfo n2 = getNeighbour(n1.neighbour, crack, init);

        //Include new points on the mesh
        this->points.push_back(n1.intersection);
        this->points.push_back(n2.intersection);

        int p1 = this->points.size()-2;
        int p2 = this->points.size()-1;

        //Split the old polygon and generate new ones
        std::vector<int> new1 = {p1, p2};
        std::vector<int> new2 = {p2, p1};

        n1.orderCCW(this->points.getList(), poly1.getCentroid());
        n2.orderCCW(this->points.getList(), poly1.getCentroid());

        int indexOfStart,point;

        if(xpoly_utilities::orientation(points.get(p1),points.get(p2),points.get(n2.edge.getFirst()))>=0){
            indexOfStart = utilities::indexOf(poly1_points, n2.edge.getFirst());
            point = n2.edge.getFirst();
        }else{
            indexOfStart = utilities::indexOf(poly1_points, n2.edge.getSecond());
            point = n2.edge.getSecond();
        }

        bool edgePointsPassed = false;

        while(true){
            if(point==n1.edge.getFirst() || point==n1.edge.getSecond()) {
                if (edgePointsPassed){
                    break;
                } else{
                    edgePointsPassed = true;
                }
            }

            new1.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        edgePointsPassed = false;

        while (true){
            if(point==n2.edge.getFirst() || point==n2.edge.getSecond()) {
                if (edgePointsPassed){
                    break;
                } else{
                    edgePointsPassed = true;
                }
            }

            new2.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        // Create new polygons and insert them on the mesh
        oldPolygons.push_back(poly1);

        Polygon newPolygon1 (new1, this->points.getList());
        Polygon newPolygon2 (new2, this->points.getList());

        newPolygons.push_back(newPolygon1);
        this->polygons[n1.neighbour] = newPolygon1;

        newPolygons.push_back(newPolygon2);
        this->polygons.push_back(newPolygon2);

        int new_index1 = n1.neighbour;
        int new_index2 = this->polygons.size() - 1;

        // Get the edge information for the old polygon and update it
        this->edges.delete_element(n1.edge);
        this->edges.delete_element(n2.edge);

        std::vector<IndexSegment> segments1;
        std::vector<IndexSegment> segments2;

        newPolygon1.getSegments(segments1);
        newPolygon2.getSegments(segments2);

        this->edges.insert(IndexSegment(p1,p2),Neighbours(n1.neighbour,n1.neighbour));

        for (int i = 0; i < segments1.size() ; ++i) {
            this->edges.replace_neighbour(segments1[i], n1.neighbour, new_index1);
        }

        for (int i = 0; i < segments2.size() ; ++i) {
            this->edges.replace_neighbour(segments2[i], n1.neighbour, new_index2);
        }

        this->edges.insert(IndexSegment(p1,n1.edge.getFirst()), init);
        this->edges.insert(IndexSegment(p1,n1.edge.getSecond()), init);
        this->edges.insert(IndexSegment(p2,n2.edge.getFirst()), n2.neighbour);
        this->edges.insert(IndexSegment(p2,n2.edge.getSecond()), n2.neighbour);

        // Iterate
        init = n1.neighbour;
        n1 = n2;
    }
}

void BreakableMesh::swapPolygons(int first, int last) {
    Polygon p1 = getPolygon(first);
    Polygon p2 = getPolygon(last);

    std::vector<IndexSegment> firstSegments;
    p1.getSegments(firstSegments);

    std::vector<IndexSegment> lastSegments;
    p2.getSegments(lastSegments);

    for(IndexSegment s: firstSegments){
        edges.get(s).changeNeighbour(first, last);
    }

    for(IndexSegment s: lastSegments){
        edges.get(s).changeNeighbour(last, first);
    }

    this->polygons[first] = p2;
    this->polygons[last] = p1;
}

void BreakableMesh::mergePolygons(int i1, int i2) {
    Polygon p = getPolygon(i1);

    if(areNeighbours(i1,i2)){
        //Todo: this is correct, but put a warning or error here
        return;
    }

    swapPolygons(i2, this->polygons.size()-1);

    Polygon poly1 = getPolygon(i1);
    Polygon poly2 = getPolygon(this->polygons.size() - 1);

    SimplePolygonMerger merger;

    Polygon merged =  merger.mergePolygons(poly1, poly2, points.getList());
    this->polygons[i1] = merged;

    std::vector<IndexSegment> poly2Segments;
    poly2.getSegments(poly2Segments);

    for(IndexSegment s: poly2Segments){
        edges.replace_or_delete(s, this->polygons.size() - 1, i1);
    }

    this->polygons.pop_back();
}

