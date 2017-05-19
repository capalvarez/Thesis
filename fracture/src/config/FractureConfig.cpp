#include <fracture/config/FractureConfig.h>
#include <stdexcept>

FractureConfig* FractureConfig::s_instance = nullptr;

FractureConfig::FractureConfig() {
    this->double_comparison_tolerance = 0.001;
    this->crack_growth_speed = 0.1;
    this->crack_size_ratio = 0.75;
    this->diameter_ratio = 1.0/8;
    this->rosette_angle = 45;
    this->max_iterations = 100;
}

void FractureConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void FractureConfig::setGrowthSpeed(double s) {
    this->crack_growth_speed = s;
}

void FractureConfig::setCrackRatio(double r) {
    if(r<=0 || r>=1){
        throw std::invalid_argument("Crack ratio has to be in range (0,1)");
    }
    this->crack_size_ratio = r;
}

void FractureConfig::setDiameterRatio(double r) {
    this->diameter_ratio = r;
}

void FractureConfig::setRosetteAngle(double a) {
    this->rosette_angle = a;
}

void FractureConfig::setMaxIterations(int i) {
    this->max_iterations = i;
}

double FractureConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

double FractureConfig::getSpeed() {
    return this->crack_growth_speed;
}

double FractureConfig::getRatio() {
    return this->crack_size_ratio;
}

double FractureConfig::getDiameterRatio() {
    return this->diameter_ratio;
}

double FractureConfig::getRosetteAngle() {
    return this->rosette_angle;
}

int FractureConfig::getMaxIterations() {
    return this->max_iterations;
}

FractureConfig *FractureConfig::instance() {
    if(!s_instance){
        s_instance = new FractureConfig;
    }

    return s_instance;
}
