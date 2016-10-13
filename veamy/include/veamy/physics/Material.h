#ifndef THESIS_MATERIAL_H
#define THESIS_MATERIAL_H

#include <veamy/lib/Eigen/Dense>

class Material{
private:
    double E;
    double v;
public:
    Material();
    Eigen::MatrixXd getMaterialMatrix();
    double trace();

};

#endif
