#ifndef THESIS_PROBLEM_H
#define THESIS_PROBLEM_H

#include <veamy/Veamer.h>
#include <fracture/geometry/BreakableMesh.h>
#include <veamy/physics/Material.h>

struct Problem{
    Veamer* veamer;
    BreakableMesh* mesh;

    Problem(Veamer* v, BreakableMesh* m){
        veamer = v;
        mesh = m;
    }
};


#endif