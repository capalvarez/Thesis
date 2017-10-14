#include <fracture/config/FractureConfig.h>
#include <stdexcept>

FractureConfig* FractureConfig::s_instance = nullptr;

FractureConfig::FractureConfig() {
    this->double_comparison_tolerance = 0.001;
}

void FractureConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

FractureConfig *FractureConfig::instance() {
    if(!s_instance){
        s_instance = new FractureConfig;
    }

    return s_instance;
}
