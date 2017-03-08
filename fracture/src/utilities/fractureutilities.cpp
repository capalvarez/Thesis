#include <x-poly/models/polygon/Polygon.h>
#include <set>
#include <fracture/geometry/BreakableMesh.h>

namespace fracture_utilities{
     std::vector<int> setToVector(std::set<int> index){
        std::vector<int> polys;

        for(auto p : index) {
            polys.push_back(p);
        }

        return polys;
    }
}