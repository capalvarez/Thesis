#include <math.h>
#include "testvector.h"

TEST_F(VectorTest, normTest){
    Vector vector1 (p1);
    Vector vector2 (p2);
    Vector vector3 (p3);

    ASSERT_EQ(vector1.norm(), sqrt(3));
    ASSERT_EQ(vector2.norm(), 1);
    ASSERT_EQ(vector3.norm(), 5);
}

TEST_F(VectorTest, crossTest){
    Vector* vectorI = new Vector(p4);
    Vector* vectorK = new Vector(p6);

    ASSERT_EQ(*vectorI^*vectorJ,*vectorK);
}

