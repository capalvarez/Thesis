#include "FractureSimulator.h"
#include <fracture/geometry/BrokenMeshInfo.h>

FractureSimulator::FractureSimulator(int k, Mesh mesh, Crack initial) {
    this->mesh = mesh;
    this->crack = initial;

    BrokenMeshInfo broken = mesh.breakPolygons();
    this->crack.addPolygons(broken.tipPolygons);

    this->veamer = Veamer(k);
}

void FractureSimulator::simulate(double crack_growth, int max_iter) {
    int n_iter = 0;

    while(n_iter<max_iter && this->crack.isFinished()){
        std::vector<Polygon> refinedPolygons = this->crack.prepareTip();
        this->veamer.replaceElement();

        Eigen::VectorXd u = this->veamer.simulate();
        std::vector<Polygon> affectedPolygons = this->crack.grow(u);
        this->veamer.replaceElement();
    }


}


