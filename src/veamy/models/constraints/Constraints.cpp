#include "Constraints.h"


Constraints::Constraints() {

}

void Constraints::addConstraint(Constraint *c) {
    c->addToMap(this->constraints);
}

bool Constraints::isConstrained(Point p) {
    return constraints.find(p)!=constraints.end();
}

