#include <geometry/Point.h>
#include <geometry/Segment.h>
#include <gtest/gtest.h>

class PolygonTest: public ::testing::Test{
protected:
    virtual void SetUp(){




    }

    std::vector<Point> points = {*new Point(), *new Point(), *new Point(), *new Point(),
                                 *new Point(),*new Point(),*new Point(),*new Point()};
};
