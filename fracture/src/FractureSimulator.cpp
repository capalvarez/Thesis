#include <fracture/FractureSimulator.h>
#include <fracture/config/FractureConfig.h>

FractureSimulator::FractureSimulator(const PolygonalMesh& mesh, const Crack& initial, const ProblemConditions& conditions) {
    this->mesh = BreakableMesh(mesh);
    this->crack = initial;
    this->veamer = BreakableVeamer();

    this->veamer.initProblem(this->mesh, conditions);

    PolygonChangeData initialChanges = this->crack.initializeCrack(this->mesh);
    this->veamer.replaceElements(initialChanges.oldPolygons, initialChanges.newPolygons, this->mesh.getPoints());
}

void FractureSimulator::simulate(double crack_growth) {
    FractureConfig* config = FractureConfig::instance();
    int n_iter = 0;

    while(n_iter<config->getMaxIterations() && !this->crack.isFinished()){
        PolygonChangeData refinedPolygons = this->crack.prepareTip(this->mesh);

        this->veamer.replaceElements(refinedPolygons.oldPolygons, refinedPolygons.newPolygons, this->mesh.getPoints());

        Eigen::VectorXd u = this->veamer.simulate(this->mesh);
        PolygonChangeData affectedPolygons = this->crack.grow(Problem(&this->veamer, &this->mesh), u);
        this->veamer.replaceElements(affectedPolygons.oldPolygons, affectedPolygons.newPolygons, this->mesh.getPoints());
        this->mesh.printInFile("after.txt");

        n_iter++;
    }
}


