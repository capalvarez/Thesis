#include <x-poly/voronoi/structures/Neighbours.h>

Neighbours::Neighbours() {}

Neighbours::Neighbours(int i1) {
    this->n1 = i1;
}

void Neighbours::setNeighbour(int i) {
    this->n2 = i;
}

int Neighbours::getFirst() {
    return this->n1;
}

int Neighbours::getSecond() {
    return this->n2;
}
