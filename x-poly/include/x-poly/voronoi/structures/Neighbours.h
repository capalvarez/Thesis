#ifndef THESIS_NEIGHBOURS_H
#define THESIS_NEIGHBOURS_H

class Neighbours {
private:
    int n1;
    int n2 = -1;
public:
    Neighbours();
    Neighbours(int i1);
    void setNeighbour(int i);
    int getFirst();
    int getSecond();
};


#endif 
