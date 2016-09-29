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
    int order;

    Mesh two_squares;
    Mesh hundred_square;
    Mesh random_voronoi_square;
    Mesh rectangle_hole;
    Mesh trapezoid;
    Mesh L;

    Eigen::VectorXd two_squares_rightforceX();
    Eigen::VectorXd two_squares_rightforceY();
    Eigen::VectorXd two_squares_noforces();

    Eigen::VectorXd hundredsquare_rightforceX();
    Eigen::VectorXd hundredsquare_rightforceY();
    Eigen::VectorXd hundredsquare_noforces();

    Eigen::VectorXd hundredsquare_twoforcesX();

    Eigen::VectorXd voronoi_rightforceX();
    Eigen::VectorXd voronoi_rightforceY();

    Eigen::VectorXd hole_rightforceX();
    Eigen::VectorXd hole_twoforceX();


    void loadRightForceX(Mesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadRightForceY(Mesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadNoForces(Mesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadTwoForcesX(Mesh m, Veamer& v, Segment leftSide, Segment rightSide);
public:
    NumericalTests(int order);

    void runTests();
};


#endif
