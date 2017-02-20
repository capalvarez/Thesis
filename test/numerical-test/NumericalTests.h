#ifndef THESIS_TESTS_H
#define THESIS_TESTS_H

#include <x-poly/models/PolygonalMesh.h>
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

    PolygonalMesh two_squares;
    PolygonalMesh hundred_square;
    PolygonalMesh random_voronoi_square;
    PolygonalMesh rectangle_hole;
    PolygonalMesh trapezoid;
    PolygonalMesh L;

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


<<<<<<< HEAD
    void loadRightForceX(Mesh m, Veamer& v, Segment<int> leftSide, Segment<int> rightSide);
    void loadRightForceY(Mesh m, Veamer& v, Segment<int> leftSide, Segment<int> rightSide);
    void loadNoForces(Mesh m, Veamer& v, Segment<int> leftSide, Segment<int> rightSide);
    void loadTwoForcesX(Mesh m, Veamer& v, Segment<int> leftSide, Segment<int> rightSide);
=======
    void loadRightForceX(PolygonalMesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadRightForceY(PolygonalMesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadNoForces(PolygonalMesh m, Veamer& v, Segment leftSide, Segment rightSide);
    void loadTwoForcesX(PolygonalMesh m, Veamer& v, Segment leftSide, Segment rightSide);
>>>>>>> fracture_all_neighbours
public:
    NumericalTests(int order);

    void runTests();
};


#endif
