#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/mesh/structures/IndexSegmentHasher.h>
#include <veamy/models/constraints/structures/Angle.h>

struct greater{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

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

void
RemeshAdapter::adaptToMesh(Triangulation triangulation, BreakableMesh &m, std::unordered_map<int, int> pointMap,
                           std::vector<Polygon> &newPolygons) {
    std::vector<int> t;

    return adaptToMesh(triangulation, m,
                       pointMap, t, newPolygons);
}

void
RemeshAdapter::adaptToMesh(Triangulation triangulation, BreakableMesh &mesh, std::unordered_map<int, int> pointMap,
                           std::vector<int> &tipTriangles, std::vector<Polygon> &newPolygons) {
    std::unordered_map<int,std::unordered_map<IndexSegment,std::vector<IndexSegment>,IndexSegmentHasher>> changesInNeighbours;
    std::unordered_map<int, std::vector<int>> trianglesToMerge;

    UniqueList<Point>& meshPoints = mesh.getPoints();
    std::vector<Polygon>& meshPolygons = mesh.getPolygons();
    SegmentMap& segments = mesh.getSegments();

    std::vector<Triangle> triangles = triangulation.getTriangles();
    std::vector<Point> triangulationPoints = triangulation.getPoints();

    std::vector<IndexSegment> containerSegments;
    mesh.getPolygon(this->regionIndex).getSegments(containerSegments);

    std::map<Angle,std::vector<IndexSegment>> containerSegmentsMap;

    for (IndexSegment s: containerSegments) {
        Angle angle = s.cartesianAngle(meshPoints.getList());

        std::vector<IndexSegment>& v = containerSegmentsMap[angle];
        v.push_back(s);
    }

    for (int i = 0; i < triangles.size() ; ++i) {
        bool isTipTriangle = false;
        int toMerge = 0;
        int boundaryPointIndex = -1;
        std::vector<int> oldTrianglePoints = triangles[i].getPoints();
        int n = oldTrianglePoints.size();

        std::vector<int> newTrianglePoints;

        for (int k = 0; k < n ; ++k) {
            if(oldTrianglePoints[k] == 0){
                isTipTriangle = true;
            }

            int newPoint = pointMap[oldTrianglePoints[k]];

            if(triangulationPoints[oldTrianglePoints[k]].isInBoundary()) {
                toMerge++;
                boundaryPointIndex = newPoint;
            }

            newTrianglePoints.push_back(newPoint);
        }

        Polygon newPolygon =  Polygon(newTrianglePoints, mesh.getPoints().getList());
        int index;

        //TODO: Hot fix!!!!
        if(!newPolygon.isValidPolygon()){
            continue;
        }

        if(i<1){
            meshPolygons[this->regionIndex] = newPolygon;
            index = this->regionIndex;
        }else{
            meshPolygons.push_back(newPolygon);
            index = meshPolygons.size() - 1;
        }

        newPolygons.push_back(newPolygon);
        if(isTipTriangle){
            tipTriangles.push_back(index);
        }

        if(toMerge==1){
            std::vector<int>& list = trianglesToMerge[boundaryPointIndex];
            list.push_back(index);
        }

        for (int j = 0; j < n; ++j) {
            bool changed = false;
            IndexSegment edge(newTrianglePoints[j], newTrianglePoints[(j+1)%n]);
            IndexSegment originalEdge(oldTrianglePoints[j],oldTrianglePoints[(j+1)%n]);

            if(originalEdge.isBoundary(triangulation.getPoints())){
                Angle a = edge.cartesianAngle(meshPoints.getList());
                std::vector<IndexSegment> containerCandidates = containerSegmentsMap[a];

                for (int k = 0; k < containerCandidates.size(); ++k) {
                    if(containerCandidates[k].contains(meshPoints.getList(),edge)){
                        Neighbours neighbours = segments.get(containerCandidates[k]);

                        bool is_first = neighbours.getFirst() == this->regionIndex;

                        int otherNeighbour = is_first? neighbours.getSecond() : neighbours.getFirst();

                        segments.insert(edge, Neighbours(index, otherNeighbour));

                        std::unordered_map<IndexSegment,std::vector<IndexSegment>,IndexSegmentHasher>& polyInfo =
                                changesInNeighbours[otherNeighbour];
                        polyInfo[containerCandidates[k]].push_back(edge);

                        changed = true;
                        break;
                    }
                }

                if(!changed){
                    //ToDO: Quickfix for border case
                    segments.insert(edge, index);
                }
            }else{
                segments.insert(edge,index);
            }
        }
    }

    for(auto value: changesInNeighbours){
        if(value.first<0)
            continue;

        Polygon& poly = meshPolygons[value.first];

        for(auto s: value.second){
            poly.replace_segment(s.first, s.second, meshPoints.getList());
        }
    }

    std::unordered_map<int,int> equivalence;
    for (auto value: trianglesToMerge){
        std::vector<int> toMerge;
        for(int i=0;i<value.second.size();i++){
            toMerge.push_back(getEquivalentIndex(equivalence,value.second[i]));
        }

        int n = mesh.numberOfPolygons() - 1;
        mesh.mergePolygons(toMerge);

        for(int i=0; i < toMerge.size()-1; i++){
            int index = n - i;
            equivalence[index] = toMerge[i];
        }
        mesh.printInFile("iammerging.txt");
    }
}

Triangulation RemeshAdapter::triangulate(std::vector<Point> points, std::vector<Point> meshPoints) {
    Region r (region, meshPoints);
    TriangleMeshGenerator generator(points, r);
    Triangulation triangulation = generator.getDelaunayTriangulation();

    return triangulation;
}

Triangulation RemeshAdapter::triangulate(Region region, std::vector<Point> points) {
    TriangleMeshGenerator generator(points, region);
    Triangulation triangulation = generator.getDelaunayTriangulation();

    return triangulation;
}

std::unordered_map<int, int> RemeshAdapter::includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation) {
    std::vector<Point> trianglePoints = triangulation.getPoints();
    return includeNewPoints(meshPoints, trianglePoints);
}

std::unordered_map<int, int> RemeshAdapter::includeNewPoints(UniqueList<Point> &meshPoints, std::vector<Point> points) {
    std::unordered_map<int,int> pointMap;

    for (int j = 0; j < points.size() ; ++j) {
        int pointIndex = meshPoints.push_back(points[j]);
        pointMap.insert(std::make_pair(j,pointIndex));
    }

    return pointMap;
}

std::vector<Polygon> RemeshAdapter::remesh(std::vector<Point> points, BreakableMesh &m) {
    std::vector<int> indexes;
    std::vector<Polygon> newPolygons;
    Triangulation t = this->triangulate(points, m.getPoints().getList());

    std::unordered_map<int,int> pointMap = this->includeNewPoints(m.getPoints(), t);

    adaptToMesh(t, m,  pointMap, newPolygons);
    return newPolygons;
}

Polygon RemeshAdapter::getRegion() {
    return this->region;
}

int RemeshAdapter::getRegionIndex() {
    return this->regionIndex;
}

int RemeshAdapter::getEquivalentIndex(std::unordered_map<int, int> map, int index) {
    auto iter = map.find(index);

    if(iter!=map.end()){
        int i = iter->second;
        iter = map.find(i);

        while(iter!=map.end()){
            i = iter->second;
            iter = map.find(i);
        }

        return i;
    }else{
        return index;
    }
}
