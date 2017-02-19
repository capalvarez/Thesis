#include <veamy/physics/Material.h>


Material::Material() {
    this->v = 0.3;
    this->E = 210000000000;
}

Eigen::MatrixXd Material::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->E)/((1 + this->v)*(1 - 2*this->v));

    D(0,0) = c*(1 - this->v);
    D(1,1) = c*(1 - this->v);
    D(2,2) = 2*c*(1 - 2*this->v);

    return D;
}

double Material::trace() {
    double c = (this->E)/((1 + this->v)*(1 - 2*this->v));

    return 2*c*((1 - this->v)+(1 - 2*this->v));
}

double Material::stressIntensityFactor() {
    return this->E/(12*(1 + this->v)*(1 - this->v));
}




