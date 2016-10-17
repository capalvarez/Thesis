#ifndef MAPDATA_H
#define MAPDATA_H

#include <functional>

struct Key {
    int first;
    int second;

    Key(int f, int s){first=f; second=s;}

    bool operator==(const Key &other) const{
        return first == other.first && second == other.second ||
               first == other.second && second == other.first;
    }
};

struct KeyHasher {
    std::size_t operator()(const Key &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.first) + hash<int>()(k.second);
    }
};

struct SegmentHasher {
    std::size_t operator()(const Segment<int> &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.getFirst()) + hash<int>()(k.getSecond());
    }
};

#endif