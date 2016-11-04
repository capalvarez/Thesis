#include <fracture/crack/CrackTip.h>

CrackTip::CrackTip(Segment<Point> crack, double speed, double radius) {
    this->speed = speed;
    this->radius = radius;
    crackPath.push_back(crack.getSecond());
    crackPath.push_back(crack.getFirst());
}

void CrackTip::addPointToPath(double angle) {
    Point last = crackPath.back();

    Point newPoint(last.getX() + this->speed*std::cos(utilities::radian(angle)),
                   last.getY() + this->speed*std::sin(utilities::radian(angle)));

    this->crackPath.push_back(newPoint);
}

CrackTip::CrackTip(const CrackTip &t) {
    this->points = t.points;
    this->container_polygon = t.container_polygon;
    this->crackAngle = t.crackAngle;
    this->crackPath = t.crackPath;
    this->speed = t.speed;
    this->radius = t.radius;
}

double CrackTip::calculateAngle(Problem problem, Eigen::VectorXd u) {
    Pair<int> dofB = problem.veamer->pointToDOFS(this->points.b);
    Pair<int> dofC = problem.veamer->pointToDOFS(this->points.c);
    Pair<int> dofD = problem.veamer->pointToDOFS(this->points.d);
    Pair<int> dofE = problem.veamer->pointToDOFS(this->points.e);

    double factor = problem.veamer->getMaterial().stressIntensityFactor()*std::sqrt(2*M_PI/this->radius)*
                    1/std::cos(utilities::radian(this->crackAngle));

    double kI = factor * (4*(u[dofB.second] - u[dofD.second]) - (u[dofC.second] - u[dofE.second])/2);
    double kII = factor * (4*(u[dofB.first] - u[dofD.first]) - (u[dofC.first] - u[dofE.first])/2);


    if(kII!=0){
        double r = kI/kII;

        return 2*std::atan(r/4 - utilities::sign(kII)/4*std::sqrt((std::pow(r,2) + 8)))  + this->crackAngle;
    }else{
        return this->crackAngle;
    }
}

PolygonChangeData CrackTip::grow(Eigen::VectorXd u, Problem problem) {
    double angle = calculateAngle(problem, u);
    Point lastPoint = crackPath.back();
    addPointToPath(angle);

    PolygonChangeData changeData = problem.mesh->breakMesh(this->container_polygon, Segment<Point>(lastPoint, crackPath.back()));
    assignLocation(changeData.lastPolygon);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh& mesh) {
    this->crackAngle = Segment<Point>(crackPath.back(), crackPath[crackPath.size() - 2]).cartesianAngle(crackPath);
    Polygon container = mesh.getPolygon(this->container_polygon);
    std::vector<Polygon> newPolygons;

    // TODO: I know 45 is about right, but don't hardcode it
    RosetteGroupGenerator rosette = RosetteGroupGenerator(this->getPoint(), this->radius, 45, container_polygon, container);
    std::vector<Point> rosettePoints = rosette.getPoints(this->crackAngle, mesh);

    std::vector<Polygon> polys = rosette.getChangedPolygons(mesh);

    int maxScale = 100000;
    ClipperLib::Paths merged = ClipperWrapper::polyUnion(polys, mesh.getPoints().getList(), maxScale);
    std::vector<Point> containerPoints;

    if(merged.size()==1){
        for (int i = 0; i < merged[0].size(); ++i) {
            containerPoints.push_back(Point(merged[0][i].X/(1.0*maxScale), merged[0][i].Y/(1.0*maxScale)));
        }
    }else{
        throw std::uncaught_exception();
    }

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

    this->points = CrackTipPoints(pointMap[1], pointMap[2], pointMap[3], pointMap[4]);
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

        newPolygons.push_back(newPolygon);

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
    return PolygonChangeData(container, newPolygons);
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

