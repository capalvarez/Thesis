#ifndef THESIS_MESHGENERATOR_H
#define THESIS_MESHGENERATOR_H

#include <x-poly/models/PolygonalMesh.h>

class MeshGenerator {
public:
    virtual PolygonalMesh getMesh() = 0;
};


#endif
