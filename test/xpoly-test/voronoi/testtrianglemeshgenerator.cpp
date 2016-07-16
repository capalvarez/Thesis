#include <x-poly/models/Mesh.h>
#include "testtrianglemeshgenerator.h"

TEST_F(TriangleMeshGeneratorTest, VoronoiTest){
    Mesh m = generator->getMesh();

    std::vector<Point> expectedPoints = {Point(0,0.5), Point(0.5,0), Point(0.5,1), Point(1,0.5),
                                         Point(0,0), Point(1,0), Point(1,1),Point(0,1)};

    EXPECT_EQ(m.getPoints(), expectedPoints);
}