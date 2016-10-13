#ifndef THESIS_POLYGONCHANGEDATA_H
#define THESIS_POLYGONCHANGEDATA_H

struct PolygonChangeData{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP){
        oldPolygons = oldP;
        newPolygons = newP;
    }
};


#endif
