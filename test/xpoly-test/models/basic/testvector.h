#ifndef THESIS_TESTVECTOR_H
#define THESIS_TESTVECTOR_H

#include <models/basic/Point3D.h>
#include <gtest/gtest.h>

class VectorTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        p1 = new Point3D (1,1,1);
        p2 = new Point3D (0,-1,0);
        p3 = new Point3D(-3,-4,0);
        p4 = new Point3D (1,0,0);
        p5 = new Point3D (0,1,0);
        p6 = new Point3D(0,0,1);

        vectorJ = new Vector(p5);
    }

    Point3D *p1,*p2,*p3,*p4,*p5,*p6;
    Vector* vectorJ;
};

#endif //THESIS_TESTVECTOR_H
