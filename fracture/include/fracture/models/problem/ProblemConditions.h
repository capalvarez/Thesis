#ifndef THESIS_PROBLEMCONDITIONS_H
#define THESIS_PROBLEMCONDITIONS_H

struct ProblemConditions{
    ConstraintsContainer constraints;
    BodyForce* f;

    ProblemConditions(ConstraintsContainer container, BodyForce* bodyForce){
        constraints = container;
        f = bodyForce;
    }
};


#endif 
