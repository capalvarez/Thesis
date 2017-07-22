#include <string>
#include <chrono>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/ProblemConditions.h>
#include <veamy/Veamer.h>


int main(){
    int n = 7;
    int sizes[] = {2, 7, 10, 15, 20 , 25, 25};
    int sizes1[] = {5, 15, 20, 20, 25 , 30, 40};
    std::vector<Point> square_points = {Point(0,0), Point(0,100), Point(100,100), Point(100,0)};
    Region square(square_points);

    std::string voronoiResultsFile = "voronoiResults.txt";
    std::string vemResultsFile = "vemResults.txt";

    std::string path = utilities::getPath();

    std::ofstream voronoiFile, vemFile;
    voronoiFile.open(path + voronoiResultsFile, std::ios::out);
    vemFile.open(path + vemResultsFile, std::ios::out);

    for (int i = 0; i < n; ++i) {
        square.generateSeedPoints(PointGenerator(functions::random_double(0,100), functions::random_double(0,100)),
                                  sizes[i], sizes1[i]);

        std::vector<Point> seeds = square.getSeedPoints();
        TriangleMeshGenerator g(seeds, square);

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        PolygonalMesh m = g.getMesh();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        voronoiFile << utilities::toString(sizes[i]*sizes1[i]) << " " << duration << std::endl;

        Veamer v;
        EssentialConstraints c;
        PointSegment constrained(Point(0,0),Point(0,100));
        Constraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

        NaturalConstraints natural;
        PointSegment const3(Point(100,0),Point(100,100));
        Constraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1000));
        natural.addConstraint(constraint3, m.getPoints().getList());

        ConstraintsContainer container;
        container.addConstraints(c, m);
        container.addConstraints(natural,m);

        ProblemConditions conditions(container, Material(Materials::material::Steel));

        t1 = std::chrono::high_resolution_clock::now();
        v.initProblem(m, conditions);
        Eigen::VectorXd x = v.simulate(m);
        t2 = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vemFile << utilities::toString(sizes[i]*sizes1[i]) << " " << duration << std::endl;
    }
}