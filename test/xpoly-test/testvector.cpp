#include <math.h>
#include <gtest/gtest.h>
#include <geometry/Point3D.h>

TEST(VectorTest, normTest){
    Point3D* p = new Point3D (1,1,1);
    Point3D* p2 = new Point3D (0,-1,0);
    Point3D* p3 = new Point3D(-3,-4,0);
    Vector vector1 (p);
    Vector vector2 (p2);
    Vector vector3 (p3);

    ASSERT_EQ(vector1.norm(), sqrt(3));
    ASSERT_EQ(vector2.norm(), 1);
    ASSERT_EQ(vector3.norm(), 5);
}

TEST(VectorTest, crossTest){



}

