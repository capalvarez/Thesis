#include <math.h>
#include <gtest/gtest.h>
#include <geometry/Point3D.h>

TEST(VectorTest, normTest){
    Point3D p (1,1,1);
    Point3D p2 (0,-1,0);
    Vector vector1 (&p);
    Vector vector2 (&p2);

    ASSERT_EQ(vector1.norm(), sqrt(3));
    ASSERT_EQ(vector2.norm(), 1);
}

TEST(VectorTest, crossTest){



}

