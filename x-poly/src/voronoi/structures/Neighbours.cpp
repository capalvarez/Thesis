#include <x-poly/voronoi/structures/Neighbours.h>
#include <assert.h>

Neighbours::Neighbours() {}

Neighbours::Neighbours(int i1) {
    this->n1 = i1;
}

Neighbours::Neighbours(int i1, int i2) {
    this->n1 = i1;
    this->n2 = i2;
}

void Neighbours::setNeighbour(int i) {
    this->n2 = i;
}

void Neighbours::changeNeighbour(int oldN, int newN) {
    if(this->n1==oldN){
        this->n1 = newN;
        return;
    }

    if(this->n2==oldN){
        this->n2 = newN;
        return;
    }

    assert(0==0 && "This should not happen :C");
}

int Neighbours::getFirst() {
    return this->n1;
}

int Neighbours::getSecond() {
    return this->n2;
}