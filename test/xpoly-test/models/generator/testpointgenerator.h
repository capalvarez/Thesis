#ifndef THESIS_TESTPOINTGENERATOR_H
#define THESIS_TESTPOINTGENERATOR_H

#include <gtest/gtest.h>
#include <models/generator/PointGenerator.h>
#include <models/generator/functions.h>

class PointGeneratorTest : public ::testing::Test {
protected:
    Rectangle* box = new Rectangle(Point(0,0), Point(10,10));
    PointGenerator* const_const = new PointGenerator(functions::constant(), functions::constant());
};


#endif
