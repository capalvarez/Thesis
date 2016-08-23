#include <gtest/gtest.h>
#include <Veamer.h>

TEST(VeamerTest, LoadDataFirstOrderTest){
    Veamer v(1);
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(2,1), Point(1,1), Point(0,1)};
    std::vector<int> p1 ={0,1,4,5};
    std::vector<int> p2 ={1,2,3,4};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    std::vector<Segment> segments;

    Mesh m (points,polygons,segments);
    v.loadData(m);

    std::vector<Element> elements = v.getElements();

    std::cout << elements[0].getK() << std::endl;



}

