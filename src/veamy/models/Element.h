#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/matrix/dof/DOF.h>

class Element {
private:
    std::vector<DOF*> dofs;
public:
    Element(Polygon p, std::vector<Point> points, int k);

};


#endif //THESIS_ELEMENT_H
