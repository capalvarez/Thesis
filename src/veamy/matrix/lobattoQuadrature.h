#ifndef THESIS_LOBATTOQUADRATURE_H
#define THESIS_LOBATTOQUADRATURE_H

#include <stdexcept>
#include <vector>

namespace lobatto {
    extern void lobatto_set(int order, std::vector<double>& xtab, std::vector<double>& weight);
}

#endif
