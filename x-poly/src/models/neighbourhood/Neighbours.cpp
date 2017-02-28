#include <x-poly/models/neighbourhood/Neighbours.h>

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

    throw std::invalid_argument("Please assign an existant neighbour");
}

int Neighbours::getFirst() const{
    return this->n1;
}

int Neighbours::getSecond() const{
    return this->n2;
}

std::string Neighbours::getString() const {
    return utilities::toString<double>(this->n1) + " " + utilities::toString<double>(this->n2);
}

bool Neighbours::operator==(const Neighbours &other) {
    return this->getFirst()==other.getFirst() && this->getSecond()==other.getSecond() ||
           this->getFirst()==other.getSecond() && this->getSecond()==other.getFirst();
}
