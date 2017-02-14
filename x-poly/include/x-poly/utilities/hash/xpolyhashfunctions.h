#ifndef THESIS_XPOLYHASHFUNCTIONS_H
#define THESIS_XPOLYHASHFUNCTIONS_H

#include <x-poly/models/polygon/Polygon.h>

namespace std{
    template <>
    struct hash<Point> {
        size_t operator()(const Point& k) const {
            return std::hash<double>()(k.getX()) ^ std::hash<double>()(k.getY());
        }
    };

    template <>
    struct hash<Polygon> {
        size_t operator()(const Polygon& k) const {
            return k.hash;
        }
    };

    template <>
    struct hash<IndexSegment>{
        size_t operator()(const IndexSegment &k) const {
            return hash<int>()(k.getFirst()) + hash<int>()(k.getSecond());
        }
    };
}



#endif 
