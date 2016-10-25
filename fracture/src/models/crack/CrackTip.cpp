#include <fracture/models/crack/CrackTip.h>
#include <fracture/models/geometry/generator/RosetteGroupGenerator.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

CrackTip::CrackTip(Segment<Point> crack, double length) {
    this->length = length;
    crackPath.push_back(crack.getSecond());
    crackPath.push_back(crack.getFirst());
}

void CrackTip::addPointToPath(double angle) {

}

double CrackTip::calculateAngle() {

    return 0;
}

Segment<Point> CrackTip::grow(BreakableMesh mesh, Eigen::VectorXd u) {




}

PolygonChangeData CrackTip::prepareTip(BreakableMesh mesh) {
    Polygon container = mesh.getPolygon(this->container_polygon);

    std::vector<Point> rosettePoints = RosetteGroupGenerator(this->getPoint(), 0.1, 0.2, 90).getPoints();
    std::vector<Point> containerPoints = container.getPoints(mesh.getPoints().getList());

    std::vector<Polygon>& meshPolygons = mesh.getPolygons();
    List<Point>& meshPoints = mesh.getPoints();

    Region containerRegion (containerPoints);

    TriangleMeshGenerator generator(rosettePoints, containerRegion);
    Triangulation triangulation = generator.getDelaunayTriangulation();

    std::unordered_map<int,int> pointMap;
    std::vector<Point> trianglePoints = triangulation.getPoints();

    for (int j = 0; j < trianglePoints.size() ; ++j) {
        int pointIndex = meshPoints.push_back(trianglePoints[j]);
        pointMap.insert(std::make_pair(j,pointIndex));
    }


    std::vector<Triangle> triangles = triangulation.getTriangles();



    for (int i = 1; i < triangles.size() ; ++i) {

    }





    return PolygonChangeData(std::vector<Polygon>(), std::vector<Polygon>(), 0);

}

bool CrackTip::isFinished(BreakableMesh mesh) {
    return mesh.isInBoundary(crackPath.back());
}

void CrackTip::assignLocation(int polygon) {
    this->container_polygon = polygon;
}

CrackTip::CrackTip() {}

Point CrackTip::getPoint() {
    return this->crackPath.back();
}




