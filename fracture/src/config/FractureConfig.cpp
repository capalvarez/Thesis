#include <fracture/config/FractureConfig.h>

FractureConfig* FractureConfig::s_instance = nullptr;

FractureConfig::FractureConfig() {
    this->double_comparison_tolerance = 0.001;
    this->crack_growth_speed = 0.1;
    this->crack_size_ratio = 0.5;
    this->rossette_angle = 45;
}

void FractureConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void FractureConfig::setGrowthSpeed(double s) {
    this->crack_growth_speed = s;
}

void FractureConfig::setCrackRatio(double r) {
    this->crack_size_ratio = r;
}

void FractureConfig::setRosetteAngle(double a) {
    this->rossette_angle = a;
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

double FractureConfig::getRosetteAngle() {
    return this->rossette_angle;
}

FractureConfig *FractureConfig::instance() {
    return s_instance;
}