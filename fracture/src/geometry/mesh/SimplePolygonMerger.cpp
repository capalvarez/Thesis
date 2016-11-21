#include <fracture/geometry/mesh/SimplePolygonMerger.h>
#include <algorithm>
#include <map>

Polygon SimplePolygonMerger::mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points) {
    std::vector<int> mergedPolygon;
    std::vector<int> poly1_points = p1.getPoints();
    std::vector<int> poly2_points = p2.getPoints();

    Pair<int> endPoints = p1.commonEdgesBorder(p2);
    int firstPointIndex = utilities::indexOf(poly1_points, endPoints.first);
    int i, init, end;

    if(p2.isPoint(poly1_points[(firstPointIndex+1)%p1.numberOfSides()])) {
        i = utilities::indexOf(poly1_points, endPoints.second);
        init = endPoints.second;
        end = endPoints.first;
    } else {
        i = firstPointIndex;
        init = endPoints.first;
        end = endPoints.second;
    }

    while(poly1_points[i]!=end){
        mergedPolygon.push_back(poly1_points[i%p1.numberOfSides()]);
        i++;
    }

    int secondPointIndex = utilities::indexOf(poly2_points, end);
    i = secondPointIndex;

    while(poly2_points[i]!=init){
        mergedPolygon.push_back(poly2_points[i%p2.numberOfSides()]);
        i++;
    }

    return Polygon(mergedPolygon, points);
}

Polygon SimplePolygonMerger::mergePolygons(std::vector<Polygon> polygons, std::vector<Point> points) {
    Polygon merged = this->mergePolygons(polygons[0], polygons[1], points);

    for(int i=2; i<polygons.size(); i++){
        merged = this->mergePolygons(merged, polygons[i], points);
    }

    return merged;
}


