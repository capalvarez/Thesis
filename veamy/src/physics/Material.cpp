#include <veamy/physics/Material.h>


Material::Material() {
    this->v = 0.33;
    this->E = 25;
}

Eigen::MatrixXd Material::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->E)/((1 + this->v)*(1 - 2*this->v));

    D(0,0) = c*(1 - this->v);
    D(1,1) = c*(1 - this->v);
    D(2,2) = 2*c*(1 - this->v);

    return D;
}




