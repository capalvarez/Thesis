#ifndef THESIS_FRACTUREUTILITIES_H
#define THESIS_FRACTUREUTILITIES_H

#include <x-poly/models/polygon/Polygon.h>
#include <set>
#include <fracture/geometry/BreakableMesh.h>

namespace fracture_utilities{
    extern std::vector<Polygon> setToVector(std::set<int> index, BreakableMesh mesh);
}

#endif 