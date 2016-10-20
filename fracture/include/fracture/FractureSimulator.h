#ifndef THESIS_FRACTURESIMULATOR_H
#define THESIS_FRACTURESIMULATOR_H

#include <x-poly/models/Mesh.h>
#include <veamy/Veamer.h>
#include <fracture/models/crack/Crack.h>
#include <fracture/models/geometry/BreakableMesh.h>
#include <fracture/models/problem/ProblemConditions.h>

class FractureSimulator {
private:
    Veamer veamer;
    BreakableMesh mesh;
    Crack crack;
public:
    FractureSimulator(Mesh mesh, Crack initial, ProblemConditions conditions);
    void simulate(double crack_growth, int max_iter);
};


#endif
