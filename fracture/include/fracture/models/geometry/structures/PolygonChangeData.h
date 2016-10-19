#ifndef THESIS_POLYGONCHANGEDATA_H
#define THESIS_POLYGONCHANGEDATA_H

struct PolygonChangeData{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;
    Polygon lastPolygon;

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP, Polygon last){
        oldPolygons = oldP;
        newPolygons = newP;
        lastPolygon = last;
    }
};


#endif
