#ifndef THESIS_FRACTUREUTILITIES_H
#define THESIS_FRACTUREUTILITIES_H

#include <x-poly/models/polygon/Polygon.h>
#include <set>
#include <fracture/geometry/BreakableMesh.h>

namespace fracture_utilities{
    extern void allPairs(std::vector<Pair<int>>& pairs, std::vector<int> numbers);
}

#endif 
