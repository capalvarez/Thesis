#include <gtest/gtest.h>
#include <fracture/crack/CrackTip.h>
#include <x-poly/models/generator/functions.h>

TEST(CrackTipTest, PrepareTipTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generateSeedPoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    PointSegment crack(Point(0.25,0.25), Point(2.75,1.5));

    CrackTip tip(crack.getFirst());
    tip.assignLocation(breakableMesh.findContainerPolygon(crack.getFirst()));
    tip.prepareTip(breakableMesh, 1, {0, 0}, 0);

}

TEST(CrackTipTest, AddPointToPathTest){
    PointSegment crack (Point(1,1), Point(0,0));

    CrackTip tip(crack.getFirst());

    tip.addPointToPath(0, BreakableMesh());
    EXPECT_EQ(tip.getPoint(), Point(1.1,1));

    tip.addPointToPath(90, BreakableMesh());
    EXPECT_EQ(tip.getPoint(), Point(1.1,1.1));

    tip.addPointToPath(30, BreakableMesh());
    EXPECT_EQ(tip.getPoint(), Point(1.1866,1.15));
}

TEST(CrackTipTest, CalculateAngleTest){

}

TEST(CrackTipTest, GrowTest){

}