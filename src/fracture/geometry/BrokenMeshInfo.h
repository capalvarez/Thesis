#ifndef THESIS_BROKENMESHINFO_H
#define THESIS_BROKENMESHINFO_H

struct BrokenMeshInfo{
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;
    std::vector<Polygon> tipPolygons;

    brokenMeshInfo(std::vector<Polygon> o, std::vector<Polygon> n, std::vector<Polygon> t){
        oldPolygons = o;
        newPolygons = n;
        tipPolygons = t;
    }

};


#endif
