#ifndef THESIS_POLYGONCHANGEDATA_H
#define THESIS_POLYGONCHANGEDATA_H

#include <x-poly/models/polygon/Polygon.h>

struct PolygonChangeData{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;
    int lastPolygon;

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP, int last){
        oldPolygons = oldP;
        newPolygons = newP;
        lastPolygon = last;
    }

    PolygonChangeData(Polygon oldP, std::vector<Polygon> newP){
        oldPolygons.push_back(oldP);
        newPolygons = newP;
    }

    PolygonChangeData(std::vector<Polygon> oldP, std::vector<Polygon> newP){
        oldPolygons = oldP;
        newPolygons = newP;
    }


};

#endif