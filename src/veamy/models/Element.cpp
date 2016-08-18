#include <x-poly/models/polygon/Polygon.h>
#include <matrix/dof/VertexDOF.h>
#include "Element.h"

Element::Element(Polygon p, std::vector <Point> points, int k) {
    std::vector<int> vertex = p.getPoints();
    for(int i=0;i<vertex.size();i++){
        //dofs.push_back(new VertexDOF())


    }



}

