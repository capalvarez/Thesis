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
    PolygonalMesh rectangleUniform;
    PolygonalMesh rectangleRandom;
    PolygonalMesh rectangle4x8Random;
    PolygonalMesh rectangle4x8ConstantAlternating;

    Eigen::VectorXd loadBothSides(PolygonalMesh mesh, std::vector<PointSegment> restrained, std::vector<double> values);
    Eigen::VectorXd clampedWithLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted, double loadValue);
    Eigen::VectorXd clampedWithParabolicLoad(PolygonalMesh mesh);
    Eigen::VectorXd fixedXWithParabolicLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted);
    Eigen::VectorXd clampedWithBodyForce(PolygonalMesh mesh, PointSegment clamped);
    Eigen::VectorXd clampedBothSideLoadMiddle(PolygonalMesh mesh);
    Eigen::VectorXd clampedDisplacement(PolygonalMesh mesh, std::vector<PointSegment> restricted, double displacement);
    Eigen::VectorXd displacementBothSides(PolygonalMesh mesh, std::vector<PointSegment> restricted,
                                              std::vector<double> displacements);
public:
    NumericalTests();
    void runTests();
};


#endif
