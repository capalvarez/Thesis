#include <fracture/geometry/mesh/SimplePolygonMerger.h>
#include <algorithm>
#include <map>
#include <fracture/geometry/BreakableMesh.h>

Polygon SimplePolygonMerger::mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points) {
    if(p1==p2){
        return p1;
    }

    std::vector<int> mergedPolygon;
    std::vector<int> poly1_points = p1.getPoints();
    std::vector<int> poly2_points = p2.getPoints();

    Pair<int> endPoints = p1.commonEdgesBorder(p2);
    int firstPointIndex = utilities::indexOf(poly1_points, endPoints.first);
    int i, init, end;

    if(p2.isVertex(poly1_points[(firstPointIndex+1)%p1.numberOfSides()])) {
        i = utilities::indexOf(poly1_points, endPoints.second);
        init = endPoints.second;
        end = endPoints.first;
    } else {
        i = firstPointIndex;
        init = endPoints.first;
        end = endPoints.second;
    }

    while(poly1_points[i]!=end){
        mergedPolygon.push_back(poly1_points[i]);
        i = (i+1)%p1.numberOfSides();
    }

    int secondPointIndex = utilities::indexOf(poly2_points, end);
    i = secondPointIndex;

    while(poly2_points[i]!=init){
        mergedPolygon.push_back(poly2_points[i]);
        i = (i+1)%p2.numberOfSides();
    }

    return Polygon(mergedPolygon, points);
}

Polygon SimplePolygonMerger::mergePolygons(std::set<int> polygons, std::vector<Point> points,
                                           BreakableMesh &mesh) {
    Polygon merged;
    std::set<int>::iterator i = polygons.end();
    std::set<int>::iterator j = polygons.begin();

    while(true){
        if(mesh.areNeighbours(*i, *j)){
            merged = this->mergePolygons(mesh.getPolygon(*i), mesh.getPolygon(*j),points);
            polygons.erase(i);
            polygons.erase(j);
            break;
        }else{
            j--;
        }
    }

    j = polygons.end();

    while(polygons.size()!=0){
        while(!mesh.areNeighbours(merged, *j)){
            if(j==polygons.begin()){
                throw std::invalid_argument("Impossible to merge polygons");
            }
            j--;
        }
        merged = this->mergePolygons(merged, mesh.getPolygon(*j) ,points);
        polygons.erase(j);
        j = polygons.end();
    }

    return merged;
}


