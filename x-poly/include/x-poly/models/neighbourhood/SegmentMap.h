#ifndef THESIS_SEGMENTMAP_H
#define THESIS_SEGMENTMAP_H


#include <x-poly/voronoi/structures/mapdata.h>
#include "utilities/Pair.h"
#include <unordered_map>
#include "Neighbours.h"
#include <fstream>
#include <x-poly/models/basic/IndexSegment.h>

class SegmentMap{
private:
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher> map;
public:
    SegmentMap();
    void insert(IndexSegment s, int polygonIndex);
    void insert(IndexSegment s, Neighbours n);
    void replace_neighbour(IndexSegment s, int oldNeighbour, int newNeighbour);
    void replace_or_delete(IndexSegment s, int oldNeighbour, int newNeighbour);
    Neighbours& get(IndexSegment s);
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher>& getMap();
    int size();
    void delete_element(IndexSegment key);
    void printInFile(std::string fileName);

};

#endif 
