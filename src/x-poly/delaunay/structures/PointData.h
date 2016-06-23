#ifndef THESIS_POINTDATA_H
#define THESIS_POINTDATA_H

class PointData{
public:
    int point;
    int edge;

    PointData(int p){this->point = p; this->edge=-1;};
    inline void setEdge(int edge, int marker){
        if(edge==-1 || marker==1) this->edge = edge;
    }
};

#endif
