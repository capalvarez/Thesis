#include <include/x-poly/models/neighbourhood/SegmentMap.h>


SegmentMap::SegmentMap() {}

void SegmentMap::insert(IndexSegment s, int polygonIndex) {
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher>::iterator got = this->map.find(s);

    if(got == this->map.end()){
        Neighbours n (polygonIndex);
        this->map.insert(std::make_pair(s,n));
    }else{
        got->second.setNeighbour(polygonIndex);
    }
}

void SegmentMap::insert(IndexSegment s, Neighbours n) {
    this->map.insert(std::make_pair(s,n));
}

void SegmentMap::replace_neighbour(IndexSegment s, int oldNeighbour, int newNeighbour) {
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher>::iterator got = this->map.find(s);

    if(got == this->map.end()){
        this->insert(s, newNeighbour);
    }else{
        got->second.changeNeighbour(oldNeighbour, newNeighbour);
    }
}

Neighbours& SegmentMap::get(IndexSegment s) {
    return map[s];
}

std::unordered_map<IndexSegment,Neighbours, SegmentHasher>& SegmentMap::getMap() {
    return this->map;
}

int SegmentMap::size() {
    return this->map.size();
}

void SegmentMap::delete_element(IndexSegment key) {
    this->map.erase(key);
}

void SegmentMap::printInFile(std::string fileName) {
    std::string path("C:\\Users\\Catalina");
    path += "\\" + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);


    for(auto v : this->map){
        file << v.first.getString() + " " + v.second.getString() << std::endl;
    }

    file.close();
}
