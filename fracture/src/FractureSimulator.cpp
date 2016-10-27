#include <fracture/FractureSimulator.h>
#include <fracture/models/geometry/structures/PolygonChangeData.h>

FractureSimulator::FractureSimulator(Mesh mesh, Crack initial, ProblemConditions conditions) {
    this->mesh = BreakableMesh(mesh);
    this->crack = initial;
    this->veamer = Veamer();

    this->veamer.loadGeometry(mesh, conditions.constraints, conditions.f);

    PolygonChangeData initialChanges = this->crack.initializeCrack(this->mesh);
    this->veamer.replaceElements(initialChanges.oldPolygons, initialChanges.newPolygons);
}

void FractureSimulator::simulate(double crack_growth, int max_iter) {
    int n_iter = 0;

    while(n_iter<max_iter && this->crack.isFinished(this->mesh)){
        PolygonChangeData refinedPolygons = this->crack.prepareTip(this->mesh);
        this->veamer.replaceElements(refinedPolygons.oldPolygons, refinedPolygons.newPolygons);

        Eigen::VectorXd u = this->veamer.simulate();
        PolygonChangeData affectedPolygons = this->crack.grow(Problem(&this->veamer, &this->mesh, ), u);
        this->veamer.replaceElements(affectedPolygons.oldPolygons, affectedPolygons.newPolygons);
    }


}


