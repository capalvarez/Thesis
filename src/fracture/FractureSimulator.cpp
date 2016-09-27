#include "FractureSimulator.h"


FractureSimulator::FractureSimulator(int k, Mesh mesh, Crack initial) {
    this->m = mesh;
    this->v = Veamer(k);
    this->crack = initial;
}

