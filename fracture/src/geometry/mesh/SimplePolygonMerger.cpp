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

    Pair<int> endPoints = p1.commonEdgesBorder(p2, points);
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

Polygon SimplePolygonMerger::mergePolygons(std::vector<int> polygons, std::vector<Point> points,
                                           BreakableMesh &mesh) {
    Polygon merged;
    int i = polygons.size()-1;
    int j = polygons.size()-2;

    while(true){
        if(j<0){
            throw std::invalid_argument("Impossible to merge polygons");
        }

        if(mesh.areNeighbours(polygons[i], polygons[j])){
            merged = this->mergePolygons(mesh.getPolygon(polygons[i]), mesh.getPolygon(polygons[j]),points);
            polygons.erase(polygons.begin()+i);
            polygons.erase(polygons.begin()+j);
            break;
        }else{
            j--;
        }
    }

    j = polygons.size()-1;

    while(polygons.size()!=0){
        while(!mesh.areNeighbours(merged, polygons[j])){
            if(j<0){
                throw std::invalid_argument("Impossible to merge polygons");
            }
            j--;
        }
        merged = this->mergePolygons(merged, mesh.getPolygon(polygons[j]) ,points);
        polygons.erase(polygons.begin()+j);
        j = polygons.size()-1;
    }

    return merged;
}


