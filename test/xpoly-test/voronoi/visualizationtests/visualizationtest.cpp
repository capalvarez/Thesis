void generateTest(std::string testName, Region r, Hole* h, std::vector<Point> points){
    r.addHole(h);

    TriangleMeshGenerator g(points, r);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile(testName + "_triangles.txt");

    Mesh m = g.getMesh();
    m.printInFile(testName + ".txt");
}

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(square_points);

    std::vector<Point> inside_p = {Point(0.25,0.25), Point(0.75,0.25), Point(0.75,0.75), Point(0.25,0.75)};
    Hole* inside = new PolygonalHole(inside_p);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    generateTest("PolygonalInside", square, inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    Region square(square_points);
    std::vector<Point> hPoints = {Point(0.25,0.75), Point(0.75,0.75), Point(0.75,1), Point(0.25,1)};
    Hole* border = new PolygonalHole(hPoints);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0,0.5)};

    generateTest("PolygonalBorder", square, inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    Region square(square_points);
    std::vector<Point> hPoints = {Point(0.75,0.75), Point(1,0.75), Point(1,1), Point(0.75,1)};
    Hole* completely_inside = new PolygonalHole(hPoints);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    generateTest("PolygonalHoleCompletelyInBorder", square, completely_inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    Region square(square_points);
    std::vector<Point> hPoints = {Point(0.5,0), Point(1,0), Point(1,1), Point(0.5,1)};
    Hole* half = new PolygonalHole(hPoints);

    std::vector<Point> points;

    generateTest("PolygonalHoleHalfTest", square, half, points);

    /*-----------------------------------------------------------------------------------------------------*/
    Region square(square_points);
    Hole* circle = new CircularHole(Point(0.5,0.5),0.25,20);
    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,0), Point(0,0.5)};

    generateTest("CircularHoleInside", square, circle, points);

    /*-----------------------------------------------------------------------------------------------------*/

    Region square(square_points);
    Hole* border = new CircularHole(Point(0.5, 1), 0.25, 20);
    std::vector<Point> points;

    generateTest("CircularHoleBorderTest", square, border, points);
}