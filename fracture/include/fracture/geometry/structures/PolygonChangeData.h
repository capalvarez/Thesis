#ifndef THESIS_POLYGONCHANGEDATA_H
#define THESIS_POLYGONCHANGEDATA_H

#include <x-poly/models/polygon/Polygon.h>

struct PolygonChangeData{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP){
        oldPolygons = oldP;
        newPolygons = newP;
    }

    PolygonChangeData(Polygon oldP, std::vector<Polygon> newP){
        oldPolygons.push_back(oldP);
        newPolygons = newP;
    }
};

#endif