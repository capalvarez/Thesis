#include <gtest/gtest.h>
#include <x-poly/models/polygon/BoundingBox.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

TEST(BoundingBoxTest, GetSegmentsTest){
    BoundingBox box(Point(0,0), Point(1,1));
    std::vector<PointSegment> segs;
    box.getSegments(segs);

    std::vector<PointSegment> expected = {PointSegment(Point(0,0), Point(1,0)), PointSegment(Point(1,0), Point(1,1)),
                                          PointSegment(Point(1,1),Point(0,1)), PointSegment(Point(0,1), Point(0,0))};

    EXPECT_EQ(expected, segs);

    segs.clear();
    expected.clear();

    BoundingBox box2(Point(2,2), Point(1,1));
    box2.getSegments(segs);

    expected = {PointSegment(Point(2,2),Point(1,2)), PointSegment(Point(1,2), Point(1,1)),
                PointSegment(Point(1,1), Point(2,1)), PointSegment(Point(2,1), Point(2,2))};

    EXPECT_EQ(expected, segs);
}

TEST(BoundingBoxTest, FitsInsideTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
    Region square(squarePoints);
    std::vector<Point> points1 = {Point(0.5, 0.5)};

    TriangleMeshGenerator gen (points1,square);
    PolygonalMesh m = gen.getMesh();

    BoundingBox box(Point(0.3,0.3), Point(0.6,0.6));
    EXPECT_TRUE(box.fitsInsidePolygon(m.getPolygon(2), std::vector<Point>()));

    box = BoundingBox(Point(0.3,0.3), Point(0.8,0.8));
    EXPECT_FALSE(box.fitsInsidePolygon(m.getPolygon(2), std::vector<Point>()));
}