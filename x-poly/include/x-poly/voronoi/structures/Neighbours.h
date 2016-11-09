#ifndef THESIS_NEIGHBOURS_H
#define THESIS_NEIGHBOURS_H

#include <iostream>
#include <x-poly/utilities/stringUtils.h>

class Neighbours {
private:
    int n1;
    int n2 = -1;
public:
    Neighbours();
    Neighbours(int i1);
    Neighbours(int i1, int i2);
    void setNeighbour(int i);
    void changeNeighbour(int oldN, int newN);
    int getFirst();
    int getSecond();
    std::string getString() const;
};


#endif 
