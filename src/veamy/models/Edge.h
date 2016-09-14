#ifndef THESIS_EDGE_H
#define THESIS_EDGE_H

#include <x-poly/models/basic/Point.h>
#include <utilities/Pair.h>
#include <vector>
#include <models/dof/DOF.h>

class Edge {
private:
    int p1;
    int p2;
public:
    Edge(int p1, int p2);

    Pair<double> getNormal(std::vector<DOF*> dofs, std::vector<Point> points);
    double getLength(std::vector<Point> points);
    std::vector<int> getDOFsInside(int k, int numberSides);

};


#endif //THESIS_EDGE_H
