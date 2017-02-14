#ifndef THESIS_VEAMYHASHFUNCTIONS_H
#define THESIS_VEAMYHASHFUNCTIONS_H

#include <veamy/models/dof/DOF.h>

namespace std {
    template<>
    struct hash<DOF> {
        size_t operator()(const DOF &k) const {
            return std::hash<int>()(k.globalIndex());
        }
    };
}

#endif 
