#ifndef THESIS_PROBLEM_H
#define THESIS_PROBLEM_H

#include <veamy/Veamer.h>
#include <fracture/models/geometry/BreakableMesh.h>
#include <veamy/physics/Material.h>

struct Problem{
    Veamer* veamer;
    BreakableMesh* mesh;
    Material* material;

    Problem(Veamer* v, BreakableMesh* m, Material* mat){
        veamer = v;
        mesh = m;
        material = mat;
    }
};


#endif 
