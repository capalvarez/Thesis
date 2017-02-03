#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>

RemeshAdapter::RemeshAdapter(Region region) {
    this->region = region;
}

RemeshAdapter::RemeshAdapter(std::vector<Polygon> remeshPolygons, std::vector<Point> points) {
    this->region = computeRemeshRegion(remeshPolygons, points);
}

Region RemeshAdapter::computeRemeshRegion(std::vector<Polygon> remeshPolygons, std::vector<Point> points) {
    SimplePolygonMerger merger;

    Polygon merged = merger.mergePolygons(remeshPolygons, points);
    std::vector<Point> containerPoints = merged.getPoints(points);

    return  Region (containerPoints);
}

std::vector<Polygon> RemeshAdapter::adaptToMesh(Triangulation triangulation, std::vector<int> changedPolygons,
                                                PolygonalMesh &mesh,
                                                std::unordered_map<int, int> pointMap) {
    std::vector<Polygon> newPolygons;

    List<Point>& meshPoints = mesh.getPoints();
    std::vector<Polygon>& meshPolygons = mesh.getPolygons();
    SegmentMap& segments = mesh.getSegments();

    std::vector<Triangle> triangles = triangulation.getTriangles();

    std::vector<Segment<int>> containerSegments;
    for (int l = 0; l < changedPolygons.size(); ++l) {
        mesh.getPolygon(changedPolygons[l]).getSegments(containerSegments);
    }

    for (int i = 0; i < triangles.size() ; ++i) {
        std::vector<int> oldTrianglePoints = triangles[i].getPoints();
        int n = oldTrianglePoints.size();

        std::vector<int> newTrianglePoints;

        for (int k = 0; k < n ; ++k) {
            newTrianglePoints.push_back(pointMap[oldTrianglePoints[k]]);
        }

        Polygon newPolygon =  Polygon(newTrianglePoints, mesh.getPoints().getList());
        int index;

        if(i<changedPolygons.size()){
            meshPolygons[changedPolygons[i]] = newPolygon;
            index = changedPolygons[i];
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

                        bool is_first = std::find(changedPolygons.begin(), changedPolygons.end(), n.getFirst())
                                        != changedPolygons.end();

                        int otherNeighbour = is_first? n.getSecond() : n.getFirst();

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

    return newPolygons;
}

Triangulation RemeshAdapter::triangulate(std::vector<Point> points) {
    TriangleMeshGenerator generator(points, region);
    Triangulation triangulation = generator.getDelaunayTriangulation();

    return triangulation;
}

std::unordered_map<int, int> RemeshAdapter::includeNewPoints(List<Point> &meshPoints, Triangulation triangulation) {
    std::unordered_map<int,int> pointMap;
    std::vector<Point> trianglePoints = triangulation.getPoints();

    for (int j = 0; j < trianglePoints.size() ; ++j) {
        int pointIndex = meshPoints.push_back(trianglePoints[j]);
        pointMap.insert(std::make_pair(j,pointIndex));
    }

    return pointMap;
}

std::vector<Polygon> RemeshAdapter::remesh(std::vector<Point> points, std::vector<int> changedPolygons, PolygonalMesh &m) {
    Triangulation t = this->triangulate(points);
    t.writeInFile("testing.txt");

    std::unordered_map<int,int> pointMap = this->includeNewPoints(m.getPoints(), t);

    return adaptToMesh(t, changedPolygons, m, pointMap);
}
