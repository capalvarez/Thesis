#ifndef THESIS_PROBLEMCONDITIONS_H
#define THESIS_PROBLEMCONDITIONS_H

struct ProblemConditions{
    ConstraintsContainer constraints;
    BodyForce* f;
    Material material;

    ProblemConditions(ConstraintsContainer container, BodyForce* bodyForce, Material mat){
        constraints = container;
        f = bodyForce;
        material = mat;
    }
};


#endif 
