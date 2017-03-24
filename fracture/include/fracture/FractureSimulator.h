#ifndef THESIS_FRACTURESIMULATOR_H
#define THESIS_FRACTURESIMULATOR_H

#include <x-poly/models/PolygonalMesh.h>
#include <veamy/Veamer.h>
#include <fracture/crack/Crack.h>
#include <fracture/geometry/BreakableMesh.h>
#include <veamy/physics/ProblemConditions.h>
#include <fracture/geometry/structures/PolygonChangeData.h>
#include <fracture/numeric/BreakableVeamer.h>

class FractureSimulator {
private:
    BreakableVeamer veamer;
    BreakableMesh mesh;
    Crack crack;
public:
    FractureSimulator(const PolygonalMesh& mesh, const Crack& initial, const ProblemConditions& conditions);
    void simulate(double crack_growth);
};


#endif
