#include <x-poly/models/polygon/Polygon.h>
#include <set>
#include <fracture/geometry/BreakableMesh.h>

namespace fracture_utilities{
    std::vector<Polygon> setToVector(std::set<int> index, BreakableMesh mesh){
        std::vector<Polygon> polys;

        for(auto p : index) {
            polys.push_back(mesh.getPolygon(p));
        }

        return polys;
    }
}