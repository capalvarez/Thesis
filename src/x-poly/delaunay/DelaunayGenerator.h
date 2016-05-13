#ifndef THESIS_DELAUNAYGENERATOR_H
#define THESIS_DELAUNAYGENERATOR_H

#include "../geometry/Mesh.h"

class DelaunayGenerator {
public:
    virtual Mesh getDelaunayTriangulation() = 0;
};


#endif
