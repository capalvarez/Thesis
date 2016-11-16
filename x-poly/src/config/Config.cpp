#include <x-poly/config/Config.h>

Config::Config() {
    this->circle_discretization_grade = 12;
    this->double_comparison_tolerance = 0.001;
    this->scale_for_clipper = 100000;
}

void Config::setDiscretizationGrade(int d) {
    this->circle_discretization_grade = d;
}

void Config::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void Config::setScale(int s) {
    this->scale_for_clipper = s;
}

int Config::getDiscretizationGrade() {
    return this->circle_discretization_grade;
}

double Config::getTolerance() {
    return this->double_comparison_tolerance;
}

int Config::getScale() {
    return this->scale_for_clipper;
}

Config *Config::instance() {
    if(!s_instance){
        s_instance = new Config;
    }

    return s_instance;
}
