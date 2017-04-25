#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>
#include <fracture/geometry/mesh/structures/IndexSegmentHasher.h>

RemeshAdapter::RemeshAdapter(Polygon poly, int index) {
    this->region = poly;
    this->regionIndex = index;
}

RemeshAdapter::RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh) {
    std::vector<int> involved;

    this->region = computeRemeshRegion(remeshPolygons, points, mesh, involved);
}

RemeshAdapter::RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh,
                             std::vector<int> &involved) {
    this->region = computeRemeshRegion(remeshPolygons, points, mesh, involved);
}

Polygon RemeshAdapter::computeRemeshRegion(std::vector<int> remeshPolygons, std::vector<Point> points,
                                          BreakableMesh &mesh, std::vector<int> &involved) {
    this->regionIndex = mesh.mergePolygons(remeshPolygons);

    Polygon merged = mesh.getPolygon(this->regionIndex);
    std::vector<int> mergedPoints = merged.getPoints();

    involved.assign(mergedPoints.begin(), mergedPoints.end());

    return  merged;
}

std::vector<Polygon>
RemeshAdapter::adaptToMesh(Triangulation triangulation, BreakableMesh &mesh, std::unordered_map<int, int> pointMap) {
    std::unordered_map<int,std::unordered_map<IndexSegment,std::vector<IndexSegment>,IndexSegmentHasher>> changesInNeighbours;
    std::vector<Polygon> newPolygons;

    UniqueList<Point>& meshPoints = mesh.getPoints();
    std::vector<Polygon>& meshPolygons = mesh.getPolygons();
    SegmentMap& segments = mesh.getSegments();

    std::vector<Triangle> triangles = triangulation.getTriangles();

    std::vector<IndexSegment> containerSegments;
    mesh.getPolygon(this->regionIndex).getSegments(containerSegments);

    for (int i = 0; i < triangles.size() ; ++i) {
        std::vector<int> oldTrianglePoints = triangles[i].getPoints();
        int n = oldTrianglePoints.size();

        std::vector<int> newTrianglePoints;

        for (int k = 0; k < n ; ++k) {
            newTrianglePoints.push_back(pointMap[oldTrianglePoints[k]]);
        }

        Polygon newPolygon =  Polygon(newTrianglePoints, mesh.getPoints().getList());
        int index;

        if(i<1){
            meshPolygons[this->regionIndex] = newPolygon;
            index = this->regionIndex;
        }else{
            meshPolygons.push_back(newPolygon);
            index = meshPolygons.size() - 1;
        }

        newPolygons.push_back(newPolygon);

        for (int j = 0; j < n; ++j) {
            IndexSegment edge(newTrianglePoints[j], newTrianglePoints[(j+1)%n]);
            IndexSegment originalEdge(oldTrianglePoints[j],oldTrianglePoints[(j+1)%n]);

            if(originalEdge.isBoundary(triangulation.getPoints())){
                for (int k = 0; k < containerSegments.size(); ++k) {
                    if(containerSegments[k].contains(meshPoints.getList(),edge)){
                        Neighbours neighbours = segments.get(containerSegments[k]);

                        bool is_first = neighbours.getFirst() == this->regionIndex;

                        int otherNeighbour = is_first? neighbours.getSecond() : neighbours.getFirst();

                        segments.insert(edge, index);
                        segments.insert(edge, otherNeighbour);

                        std::unordered_map<IndexSegment,std::vector<IndexSegment>,IndexSegmentHasher>& polyInfo =
                                changesInNeighbours[otherNeighbour];
                        polyInfo[containerSegments[k]].push_back(edge);

                        break;
                    }
                }
            }else{
                segments.insert(edge,index);
            }
        }
    }

    for(auto value: changesInNeighbours){
        Polygon& poly = meshPolygons[value.first];

        for(auto s: value.second){
            poly.replace_segment(s.first, s.second, meshPoints.getList());
        }
    }

    return newPolygons;
}

Triangulation RemeshAdapter::triangulate(std::vector<Point> points, std::vector<Point> meshPoints) {
    Region r (region, meshPoints);
    TriangleMeshGenerator generator(points, r);
    Triangulation triangulation = generator.getDelaunayTriangulation();

    return triangulation;
}

std::unordered_map<int, int> RemeshAdapter::includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation) {
    std::unordered_map<int,int> pointMap;
    std::vector<Point> trianglePoints = triangulation.getPoints();

    for (int j = 0; j < trianglePoints.size() ; ++j) {
        int pointIndex = meshPoints.push_back(trianglePoints[j]);
        pointMap.insert(std::make_pair(j,pointIndex));
    }

    return pointMap;
}

std::vector<Polygon> RemeshAdapter::remesh(std::vector<Point> points, BreakableMesh &m) {
    std::vector<int> indexes;
    Triangulation t = this->triangulate(points, m.getPoints().getList());

    std::unordered_map<int,int> pointMap = this->includeNewPoints(m.getPoints(), t);

    return adaptToMesh(t, m, pointMap);
}

Polygon RemeshAdapter::getRegion() {
    return this->region;
}

int RemeshAdapter::getRegionIndex() {
    return this->regionIndex;
}
