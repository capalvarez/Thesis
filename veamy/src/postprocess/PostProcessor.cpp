#include <veamy/postprocess/PostProcessor.h>

PostProcessor::PostProcessor(Eigen::VectorXd u, Veamer veamer) {
    this->u = u;
    this->veamer = veamer;
}

void PostProcessor::displacementsProcess(std::unordered_map<Point, double, PointHasher> &dispX,
                                         std::unordered_map<Point, double, PointHasher> &dispY) {

    std::unordered_map<int, Pair<int>> point_to_dofs = this->veamer.DOFs.point_to_dofs;
    List<Point> points = this->veamer.getPoints();

    for(auto d: point_to_dofs){
        Point p = points.get(d.first);
        Pair<int> dofs = d.second;

        dispX.insert(std::make_pair(p, u(dofs.first)));
        dispX.insert(std::make_pair(p, u(dofs.second)));
    }
}

void PostProcessor::printInFile(std::unordered_map<Point, double, PointHasher> map, std::string fileName) {
    std::string path("C:\\Users\\Catalina");
    path += "\\" + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    file << map.size() << std::endl;
    for(auto d: map){
        file << d.first.getString() + " " << d.second << std::endl;
    }

    file.close();
}


void PostProcessor::writeDisplacements(std::string fileNames[]) {
    std::unordered_map<Point,double,PointHasher> dispX;
    std::unordered_map<Point,double,PointHasher> dispY;

    this->displacementsProcess(dispX, dispY);

    this->printInFile(dispX, fileNames[0]);
    this->printInFile(dispY, fileNames[1]);
}
