#include <fracture/models/geometry/BreakableMesh.h>

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(Mesh m) {
    this->mesh = m;
}

BrokenMeshInfo BreakableMesh::breakMesh(int init, Segment<Point> crack) {
    NeighbourInfo n1 = getNeighbour(init, crack);

    while(true){
        Polygon poly1 = getPolygon(n1.neighbour);

        if(poly1.containsPoint(this->points, crack.getSecond())){
            break;
        }

        std::vector<int> poly1_points = poly1.getPoints();
        NeighbourInfo n2 = getNeighbour(n1.neighbour, crack);

        //Include new points on the mesh
        points.push_back(n1.intersection);
        points.push_back(n2.intersection);

        //Split the old polygon and generate new ones
        std::vector<int> newPolygon1 = {points.size()-2, points.size()-1};
        std::vector<int> newPolygon2 = {points.size()-1, points.size()-2};

        int indexOfStart = utilities::indexOf(poly1_points, n2.edge.getSecond());
        int point = n2.edge.getSecond();

        while(point!=n1.edge.getSecond()){
            newPolygon1.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        while (point!=n2.edge.getSecond()){
            newPolygon2.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        // Get the edge information for the old polygon and update it

        // Replace the old polygon with the new ones


        // Iterate
        n1 = n2;
    }
}


