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

Segment<Point> CrackTip::grow(BreakableMesh& mesh, Eigen::VectorXd u) {




}

PolygonChangeData CrackTip::prepareTip(BreakableMesh& mesh) {
    double crackAngle = Segment<Point>(crackPath.back(), crackPath[crackPath.size() - 2]).cartesianAngle(crackPath);
    Polygon container = mesh.getPolygon(this->container_polygon);

    std::vector<Point> rosettePoints = RosetteGroupGenerator(this->getPoint(), 0.1, 0.2, 90).getPoints(crackAngle);
    std::vector<Point> containerPoints = container.getPoints(mesh.getPoints().getList());

    std::vector<Polygon>& meshPolygons = mesh.getPolygons();
    List<Point>& meshPoints = mesh.getPoints();
    SegmentMap& segments = mesh.getSegments();

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

    std::vector<Segment<int>> containerSegments;
    container.getSegments(containerSegments);

    for (int i = 0; i < triangles.size() ; ++i) {
        std::vector<int> oldTrianglePoints = triangles[i].getPoints();
        int n = oldTrianglePoints.size();

        std::vector<int> newTrianglePoints;

        for (int k = 0; k < n ; ++k) {
            newTrianglePoints.push_back(pointMap[oldTrianglePoints[k]]);
        }

        Polygon newPolygon =  Polygon(newTrianglePoints, mesh.getPoints().getList());
        int index;

        if(i==0){
            meshPolygons[this->container_polygon] = newPolygon;
            index = 0;
        }else{
            meshPolygons.push_back(newPolygon);
            index = meshPolygons.size() - 1;
        }

        for (int j = 0; j < n; ++j) {
            Segment<int> edge(newTrianglePoints[j], newTrianglePoints[(j+1)%n]);
            Segment<int> originalEdge(oldTrianglePoints[j],oldTrianglePoints[(j+1)%n]);

            if(originalEdge.isBoundary(triangulation.getPoints())){
                for (int k = 0; k < containerSegments.size(); ++k) {
                    if(containerSegments[k].contains(meshPoints.getList(),edge)){
                        Neighbours n = segments.get(containerSegments[k]);
                        int otherNeighbour = n.getFirst()==this->container_polygon? n.getSecond() : n.getFirst();

                        segments.insert(edge, index);
                        segments.insert(edge, otherNeighbour);
                        break;
                    }
                }
            }else{
                segments.insert(edge,index);
            }
        }
    }

    for (int i = 0; i < containerSegments.size(); ++i) {
        segments.delete_element(containerSegments[i]);
    }

    mesh.printInFile("prepare.txt");

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

