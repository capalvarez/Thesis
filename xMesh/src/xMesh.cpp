#include <include/xMesh/models/xMesh.h>
#include <x-poly/models/basic/PointSegment.h>

void xMesh::breakMeshBySegment(int init, PointSegment direction, std::vector<int> previous) {
    NeighbourInfo n1 = getNeighbour(init, direction, previous);

    if(n1.neighbour<0){
        return;
    }

    int last = -1;
    //Si el inicio de la grieta está en un segmento y no en un poligono
    if(){
        IndexSegment container_edge = this->getPolygon(init).containerEdge(getPoints().getList(), crack.getFirst());
        NeighbourInfo n0 = NeighbourInfo(init, container_edge,crack.getFirst() ,false);
        n0.isVertex = container_edge.isEndPoint(crack.getFirst(), this->points.getList());

        splitPolygons(n0, n1, -1, newPoints);
        last = this->polygons.size() - 1;
    }


    bool oneLastIteration = false;

    while(true){
        DestructibleElement& element1 = getElement(n1.neighbour);

        if(poly1.containsPoint(this->points.getList(), crack.getSecond())){
            if(poly1.inEdges(this->points.getList(), crack.getSecond())){
                if(!oneLastIteration){
                    oneLastIteration = true;
                }
            }else{
                return;
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

        splitPolygons(n1, n2, init);

        // Iterate
        if(oneLastIteration){
            return;
        }

        last = this->polygons.size()-1;
        init = n1.neighbour;
        n1 = n2;
    }
}


void xMesh::breakMesh() {



}

void xMesh::merge() {

}

void xMesh::refine() {

}
