#ifndef THESIS_PAIR_H
#define THESIS_PAIR_H

#include <x-poly/config/Config.h>

template <typename T>
class Pair {
public:
    T first;
    T second;

    Pair(T first, T second);
    Pair(const Pair& other);
    Pair();
    bool operator==(const Pair& other) const;
    T dot(Pair other);
    Pair<T> average(Pair<T> other);
    Pair<T> operator*(const double other);
    Pair<T> operator+(const Pair& other) const;
};


#endif
