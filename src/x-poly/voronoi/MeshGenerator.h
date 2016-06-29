#ifndef THESIS_MESHGENERATOR_H
#define THESIS_MESHGENERATOR_H

#include "models/Mesh.h"

class MeshGenerator {
public:
    virtual Mesh getMesh() = 0;
};


#endif
