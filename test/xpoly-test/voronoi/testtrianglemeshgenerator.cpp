#include <x-poly/models/Mesh.h>
#include "testtrianglemeshgenerator.h"

TEST_F(TriangleMeshGeneratorTest, VoronoiTest){
    Mesh m = generator->getMesh();

    std::vector<Point> expectedPoints = {Point(0,0.5), Point(0.5,0), Point(0.5,1), Point(1,0.5),
                                         Point(0,0), Point(1,0), Point(1,1),Point(0,1)};
    EXPECT_EQ(m.getPoints(), expectedPoints);

    std::vector<Segment> expectedSegments = {Segment(0,1), Segment(0,2), Segment(2,3), Segment(3,1), Segment(0,4), Segment(4,1),
                                             Segment(3,5),Segment(5,1),Segment(3,6),Segment(6,2),Segment(0,7), Segment(7,2)};

    EXPECT_EQ(m.getEdges(), expectedSegments);

    std::vector<int> index0 = {1,0,2,3};
    std::vector<int> index1 = {1,0,4};
    std::vector<int> index2 = {1,3,5};
    std::vector<int> index3 = {2,3,6};
    std::vector<int> index4 = {2,0,7};

    std::vector<Polygon> expectedElements = {Polygon(index0,expectedPoints), Polygon(index1,expectedPoints),
                                             Polygon(index2,expectedPoints),Polygon(index3,expectedPoints),
                                             Polygon(index4,expectedPoints)};
    EXPECT_EQ(m.getElements(), expectedElements);

}