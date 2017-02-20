#ifndef THESIS_POSTPROCESSOR_H
#define THESIS_POSTPROCESSOR_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/Veamer.h>
#include <veamy/postprocess/structures/PointHasher.h>
#include <fstream>

class PostProcessor{
private:
    Eigen::VectorXd u;
    Veamer veamer;

    void displacementsProcess(std::unordered_map<Point, double, PointHasher> &dispX,
                                  std::unordered_map<Point, double, PointHasher> &dispY);
    void printInFile(std::unordered_map<Point, double, PointHasher> map, std::string fileName);
public:
    PostProcessor(Eigen::VectorXd u, Veamer veamer);
    void writeDisplacements(std::string fileNames[]);
};


#endif 
