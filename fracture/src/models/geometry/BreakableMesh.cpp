#include <fracture/models/geometry/BreakableMesh.h>

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(Mesh m) {
    this->mesh = m;
}

PolygonChangeData BreakableMesh::breakMesh(int init, Segment<Point> crack) {
    std::vector<Polygon> oldPolygons;


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

        int p1 = points.size()-2;
        int p2 = points.size()-1;

        //Split the old polygon and generate new ones
        std::vector<int> new1 = {p1, p2};
        std::vector<int> new2 = {p2, p1};

        int indexOfStart = utilities::indexOf(poly1_points, n2.edge.getSecond());
        int point = n2.edge.getSecond();

        while(point!=n1.edge.getSecond()){
            new1.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        while (point!=n2.edge.getSecond()){
            new2.push_back(point);
            point = poly1_points[(indexOfStart+1)%poly1_points.size()];

            indexOfStart++;
        }

        // Create new polygons and insert them on the mesh
        this->polygons.erase(this->polygons.begin() + n1.neighbour);

        Polygon newPolygon1 (new1, this->points);
        Polygon newPolygon2 (new2, this->points);

        this->polygons.push_back(newPolygon1);
        this->polygons.push_back(newPolygon2);

        int new_index1 = polygons.size() - 2;
        int new_index2 = polygons.size() - 2;

        // Get the edge information for the old polygon and update it
        edges.delete_element(n1.edge);
        edges.delete_element(n2.edge);

        std::vector<Segment<int>> segments1;
        std::vector<Segment<int>> segments2;

        newPolygon1.getSegments(segments1);
        newPolygon2.getSegments(segments2);

        for (int i = 0; i < segments1.size() ; ++i) {
            edges.replace_neighbour(segments1[i], n1.neighbour, new_index1);
        }

        for (int i = 0; i < segments2.size() ; ++i) {
            edges.replace_neighbour(segments2[i], n1.neighbour, new_index2);
        }

        // Iterate
        n1 = n2;
    }
}


