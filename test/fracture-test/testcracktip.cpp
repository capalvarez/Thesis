#include <gtest/gtest.h>
#include <fracture/crack/CrackTip.h>
#include <x-poly/models/generator/functions.h>

TEST(CrackTipTest, PrepareTipTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    Segment<Point> crack(Point(0.25,0.25), Point(2.75,1.5));

    CrackTip tip(crack, 0.1, 0.1);
    tip.assignLocation(breakableMesh.findContainerPolygon(crack.getFirst()));
    tip.prepareTip(breakableMesh);

}

TEST(CrackTipTest, AddPointToPathTest){
    Segment<Point> crack (Point(1,1), Point(0,0));

    CrackTip tip(crack, 0.1, 0.1);

    tip.addPointToPath(0);
    EXPECT_EQ(tip.getPoint(), Point(1.1,1));

    tip.addPointToPath(90);
    EXPECT_EQ(tip.getPoint(), Point(1.1,1.1));

    tip.addPointToPath(30);
    EXPECT_EQ(tip.getPoint(), Point(1.1866,1.15));
}

TEST(CrackTipTest, CalculateAngleTest){

}

TEST(CrackTipTest, GrowTest){

}