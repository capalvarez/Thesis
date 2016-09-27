#ifndef THESIS_FRACTURESIMULATOR_H
#define THESIS_FRACTURESIMULATOR_H

#include <x-poly/models/Mesh.h>
#include <veamy/Veamer.h>
#include <models/Crack.h>

class FractureSimulator {
private:
    Veamer v;
    Mesh m;
    Crack crack;
public:
    FractureSimulator(int k, Mesh mesh, Crack initial);
};


#endif
