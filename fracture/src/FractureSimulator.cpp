#include <fracture/FractureSimulator.h>
#include <fracture/config/FractureConfig.h>

FractureSimulator::FractureSimulator(std::string simulationName, const PolygonalMesh& mesh, const Crack& initial) {
    this->step = 0;
    this->simulationName = simulationName;
    this->mesh = BreakableMesh(mesh);
    this->crack = initial;

    this->mesh.printInFile("initial.txt");
    this->crack.initializeCrack(this->mesh);
}

void FractureSimulator::simulate(double crack_growth) {
    FractureConfig* config = FractureConfig::instance();
    config->setGrowthSpeed(crack_growth);

    this->writeStepInFile();

    while(this->step<config->getMaxIterations() && !this->crack.isFinished()){
        PolygonChangeData refinedPolygons = this->crack.prepareTip(this->mesh);
        this->step++;
        this->writeStepInFile();

        PolygonChangeData affectedPolygons = this->crack.grow(Problem(&this->veamer, &this->mesh), u);

        this->mesh.printInFile("after.txt");

        this->step++;
        this->writeStepInFile();
    }

    this->writeNumberOfSteps();
}

void FractureSimulator::writeStepInFile() {
    std::string fileName = utilities::getPath() + this->simulationName +"_step" + utilities::toString(step) + ".txt";
    std::ofstream file;
    file.open(fileName, std::ios::out);

    this->mesh.printInStream(file);
    this->crack.printInStream(file);

    file.close();
}

void FractureSimulator::writeNumberOfSteps() {
    std::string fileName = utilities::getPath() + this->simulationName +"number.txt";
    std::ofstream file;
    file.open(fileName, std::ios::out);

    file << utilities::toString(this->step) << std::endl;

    file.close();
}
