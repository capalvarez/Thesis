#include <veamy/config/VeamyConfig.h>

VeamyConfig* VeamyConfig::s_instance = nullptr;

VeamyConfig::VeamyConfig() {
    this->double_comparison_tolerance = 0.001;
}

void VeamyConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

double VeamyConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

VeamyConfig *VeamyConfig::instance() {
    if(!s_instance){
        s_instance = new VeamyConfig;
    }

    return s_instance;
}
