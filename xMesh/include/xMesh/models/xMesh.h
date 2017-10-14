#ifndef THESIS_DESTRUCTIBLEMESH_H
#define THESIS_DESTRUCTIBLEMESH_H

#include <x-poly/models/PolygonalMesh.h>
#include "xElement.h"
#include "xPolygon.h"

class xMesh: public Mesh{
private:
    std::vector<xPolygon> polygons;

    void breakMeshBySegment();

public:


    void breakMesh(std::vector);
    void merge();


    void refine();
};
#endif