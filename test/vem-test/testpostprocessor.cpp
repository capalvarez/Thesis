#include <gtest/gtest.h>
#include <veamy/physics/BodyForce.h>
#include <veamy/Veamer.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/postprocess/PostProcessor.h>

TEST(PostProcessorTest, DisplacementTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(3,0), Point(3,1), Point(0,1)};
    Region region(points);
    region.generatePoints(PointGenerator(functions::constant(), functions::constant()), 16, 16);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    Mesh m = g.getMesh();
    m.printInFile("Idontgetit.txt");

    EssentialConstraints c;
    Segment<Point> constrained(Point(0,0),Point(0,1));
    Segment<Point> constrained2 (Point(3,0),Point(3,1));
    Constraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1);
    Constraint const2 (constrained2, m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1));
    c.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);

    ProblemConditions conditions(container, f, Material());

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate();

    std::string files[2] = {"ux_simple.txt", "uy_simple.txt"};

    PostProcessor postProcessor (x, v);
    postProcessor.writeDisplacements(files);
}