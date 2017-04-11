#include <fracture/geometry/mesh/SimplePolygonMerger.h>
#include <algorithm>
#include <map>
#include <fracture/geometry/BreakableMesh.h>

Polygon SimplePolygonMerger::mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points) {
    if(p1==p2){
        return p1;
    }

    std::vector<int> mergedPolygon;
    std::vector<int>& poly1_points = p1.getPoints();
    std::vector<int>& poly2_points = p2.getPoints();

    bool special_case = false;
    Pair<int> endPoints = p1.commonEdgesBorder(p2, points, special_case);
    if(special_case) {
        for (int index: poly2_points){
            if(index==endPoints.first || index==endPoints.second)
                continue;

            poly1_points.erase(std::remove(poly1_points.begin(), poly1_points.end(), index), poly1_points.end());
        }

        Polygon (poly1_points, points);
        return Polygon (poly1_points, points);
    }

    int firstPointIndex_p1 = utilities::indexOf(poly1_points, endPoints.first);
    int secondPointIndex_p1 = utilities::indexOf(poly1_points, endPoints.second);
    int first_1, second_1, first_2, second_2;

    if(firstPointIndex_p1<secondPointIndex_p1) {
        first_1 = firstPointIndex_p1;
        second_1 = secondPointIndex_p1;
    } else{
        first_1 = secondPointIndex_p1;
        second_1 = firstPointIndex_p1;
    }

    if(!p2.isVertex(poly1_points[(first_1+1)%p1.numberOfSides()])) {
        int tmp = first_1;
        first_1 = second_1;
        second_1 = tmp;
    }

    int firstPointIndex_p2 = utilities::indexOf(poly2_points, endPoints.first);
    int secondPointIndex_p2 = utilities::indexOf(poly2_points, endPoints.second);

    if(firstPointIndex_p2<secondPointIndex_p2) {
        first_2 = firstPointIndex_p2;
        second_2 = secondPointIndex_p2;
    } else{
        first_2 = secondPointIndex_p2;
        second_2 = firstPointIndex_p2;
    }

    if(!p1.isVertex(poly2_points[(first_2+1)%p1.numberOfSides()])) {
        int tmp = first_2;
        first_2 = second_2;
        second_2 = tmp;
    }

    int i = (second_1 + 1)%p1.numberOfSides();
    while(i!=first_1){
        mergedPolygon.push_back(poly1_points[i]);

        i = (i+1)%p1.numberOfSides();
    }

    i = second_2;
    while(i!=first_2){
        mergedPolygon.push_back(poly2_points[i]);

        i = (i+1)%p2.numberOfSides();
    }

    mergedPolygon.push_back(poly2_points[first_2]);

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
        while(!mesh.areMergeable(merged, polygons[j])){
            if(j<0){
                throw std::invalid_argument("Impossible to merge polygons");
            }
            j--;
        }

        if(merged.containsPoint(mesh.getPoints().getList(), mesh.getPolygon(polygons[j]).getCentroid())){
            polygons.erase(polygons.begin()+j);
            j = polygons.size()-1;
            continue;
        }

        merged = this->mergePolygons(merged, mesh.getPolygon(polygons[j]) ,points);
        polygons.erase(polygons.begin()+j);
        j = polygons.size()-1;
    }

    return merged;
}


