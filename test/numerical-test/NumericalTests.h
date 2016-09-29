#ifndef THESIS_TESTS_H
#define THESIS_TESTS_H

#include <x-poly/models/Mesh.h>
#include <veamy/lib/Eigen/Dense>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/hole/CircularHole.h>
#include <iostream>
#include <veamy/physics/BodyForce.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/Veamer.h>

class NumericalTests{
private:
    Mesh one_square;
    Mesh hundred_square;
    Mesh random_voronoi_square;
    Mesh rectangle_hole;
    Mesh trapezoid;
    Mesh L;

    Eigen::VectorXd onesquare_rightforceX();
    Eigen::VectorXd onesquare_rightforceY();
    Eigen::VectorXd onesquare_noforces();

    Eigen::VectorXd hundredsquare_rightforceX();
    Eigen::VectorXd hundredsquare_rightforceY();
    Eigen::VectorXd hundredsquare_noforces();

    Eigen::VectorXd hundredsquare_twoforcesX();
    Eigen::VectorXd hundredsquare_distributedforce();

    Eigen::VectorXd voronoi_rightforceX();
    Eigen::VectorXd voronoi_rightforceY();

    Eigen::VectorXd hole_rightforceX();
    Eigen::VectorXd hole_twoforceX();

public:
    NumericalTests();

    void runTests();




};


#endif
