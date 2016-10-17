#ifndef THESIS_EDGEDATA_H
#define THESIS_EDGEDATA_H

#include <iostream>
#include <x-poly/utilities/utilities.h>

class EdgeData{
public:
    int p1;
    int p2;
    int t1;
    int t2;

    EdgeData(int p1, int p2);
    void setTriangle(int t);
    bool equals(EdgeData other);
    std::string getString();
    bool operator==(const EdgeData& other) const;
};

#endif
