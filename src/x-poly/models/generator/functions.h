#ifndef THESIS_FUNCTIONS_H
#define THESIS_FUNCTIONS_H

#include <functional>

namespace functions {
    extern std::function<double(double)> constant();
    extern std::function<double(double)> uniform(int delta);
    extern std::function<double(double)> random();
}

#endif
