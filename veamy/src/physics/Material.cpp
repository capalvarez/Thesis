#include <veamy/physics/Material.h>
#include <veamy/config/VeamyConfig.h>
#include <iostream>

Material::Material(double E, double v) {
    this->v = v;
    this->E = E;
}

Material::Material() {}

Material::Material(Materials::material m) {
    material_info info = Materials::properties[m];

    this->E = info.E;
    this->v = info.v;
}

Eigen::MatrixXd Material::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->E)/((1 + this->v)*(1 - 2*this->v));

    D(0,0) = c*(1 - this->v);
    D(0,1) = c*this->v;
  //  D(0,2) = c*this->v;

    D(1,0) = c*this->v;
    D(1,1) = c*(1 - this->v);
    //D(1,2) = c*this->v;

    //D(2,0) = c*this->v;
    //D(2,1) = c*this->v;
    //D(2,2) = c*(1 - this->v);

    D(2,2) = c*(1 - 2*this->v);
    //D(4,4) = 2*c*(1 - 2*this->v);
    //D(5,5) = 2*c*(1 - 2*this->v);

    return D;
}

double Material::trace() {
    double c = (this->E)/((1 + this->v)*(1 - 2*this->v));

    return c*(2*(1 - this->v) + 2*(1 - 2*this->v));
}

double Material::stressIntensityFactor() {
    return this->E/(12*(1 + this->v)*(1 - this->v));
}

bool Material::operator==(const Material &other) const{
    VeamyConfig* config = VeamyConfig::instance();
    return std::abs(this->E-other.E) < config->getTolerance() &&
            std::abs(this->v-other.v) < config->getTolerance();
}




