#ifndef THESIS_FRACTURESIMULATOR_H
#define THESIS_FRACTURESIMULATOR_H

#include <x-poly/models/Mesh.h>
#include <veamy/Veamer.h>
#include <models/Crack.h>

class FractureSimulator {
private:
    Veamer veamer;
    Mesh mesh;
    Crack crack;
public:
    FractureSimulator(int k, Mesh mesh, Crack initial);
    void simulate(double crack_growth, int max_iter);
};


#endif
