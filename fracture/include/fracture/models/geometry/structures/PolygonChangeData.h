#ifndef THESIS_POLYGONCHANGEDATA_H
#define THESIS_POLYGONCHANGEDATA_H

struct PolygonChangeData{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;
    int lastPolygon;

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP, int last){
        oldPolygons = oldP;
        newPolygons = newP;
        lastPolygon = last;
    }
};


#endif
