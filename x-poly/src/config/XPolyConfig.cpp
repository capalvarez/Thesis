#include <x-poly/config/XPolyConfig.h>

XPolyConfig* XPolyConfig::s_instance = nullptr;

XPolyConfig::XPolyConfig() {
    this->circle_discretization_grade = 12;
    this->double_comparison_tolerance = 0.001;
    this->scale_for_clipper = 100000;
}

void XPolyConfig::setDiscretizationGrade(int d) {
    this->circle_discretization_grade = d;
}

void XPolyConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void XPolyConfig::setScale(int s) {
    this->scale_for_clipper = s;
}

int XPolyConfig::getDiscretizationGrade() {
    return this->circle_discretization_grade;
}

double XPolyConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

int XPolyConfig::getScale() {
    return this->scale_for_clipper;
}

XPolyConfig *XPolyConfig::instance() {
    if(!s_instance){
        s_instance = new XPolyConfig;
    }

    return s_instance;
}
