#ifndef THESIS_FUNCTIONS_H
#define THESIS_FUNCTIONS_H

#include <functional>

namespace functions {
    std::function<double(double)> constant = [](double x) {return x;};
    std::function<double(double)> uniform = [](double x, double delta) { return delta*x;};
    extern std::function<double(double)> random_double(double min, double max);
    extern std::function<double(double)> random_integer(double min, double max);
    extern std::function<double(double)> sine(double amplitude, double frecuency, double phase);
    extern std::function<double(double)> cosine(double amplitude, double frecuency, double phase);
}

#endif
