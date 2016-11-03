#ifndef THESIS_FRACTURESIMULATOR_H
#define THESIS_FRACTURESIMULATOR_H

#include <x-poly/models/Mesh.h>
#include <veamy/Veamer.h>
#include <fracture/crack/Crack.h>
#include <fracture/geometry/BreakableMesh.h>
#include <veamy/physics/ProblemConditions.h>
#include <fracture/geometry/structures/PolygonChangeData.h>

class FractureSimulator {
private:
    Veamer veamer;
    BreakableMesh mesh;
    Crack crack;
public:
    FractureSimulator(const Mesh& mesh, const Crack& initial, const ProblemConditions& conditions);
    void simulate(double crack_growth, int max_iter);
};


#endif
