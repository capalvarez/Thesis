#ifndef THESIS_BROKENMESHINFO_H
#define THESIS_BROKENMESHINFO_H

struct BrokenMeshInfo{
    PolygonChangeData data;
    Polygon tipPolygon;

    BrokenMeshInfo(std::vector<Polygon> o, std::vector<Polygon> n, Polygon t){
        data = PolygonChangeData(o,p);
        tipPolygons = t;
    }

    oldPolygons(){
        return data.oldPolygons;
    }

    newPolygons(){
        return data.newPolygons;
    }

};


#endif
