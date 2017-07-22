#ifndef THESIS_TESTPOINTGENERATOR_H
#define THESIS_TESTPOINTGENERATOR_H

#include <gtest/gtest.h>
#include <x-poly/models/generator/PointGenerator.h>
#include <x-poly/models/generator/functions.h>

class PointGeneratorTest : public ::testing::Test {
protected:
    BoundingBox* box = new BoundingBox(Point(0,0), Point(10,10));
    PointGenerator* const_const = new PointGenerator(functions::constant(), functions::constant());
};


#endif
