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
    BreakableMesh mesh;
    Crack crack;

    int step;
    std::string simulationName;

    void writeStepInFile();
    void writeNumberOfSteps();
public:
    FractureSimulator(std::string simulationName, const PolygonalMesh& mesh, const Crack& initial);
    void simulate(double crack_growth);
};


#endif
