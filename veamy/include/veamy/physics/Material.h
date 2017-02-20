#ifndef THESIS_MATERIAL_H
#define THESIS_MATERIAL_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/materials/Materials.h>

class Material{
private:
    double E;
    double v;
public:
    Material(Materials::material m);
    Material(double young, double poisson);
    Material();

    Eigen::MatrixXd getMaterialMatrix();
    double trace();

    double stressIntensityFactor();
    bool operator==(const Material& other) const;
};

#endif
