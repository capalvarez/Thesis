#ifndef THESIS_UTILITIES_H
#define THESIS_UTILITIES_H

#include <vector>
#include <iostream>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/Pair.h>

namespace utilities {
    extern void TrivialIndexVector(std::vector<int>& index_vector, int n);

    template<class T>
    class DeleteVector {
    public:
        bool operator()(T x) const {
            delete x;
            return true;
        };
    };

    extern double radian(double angle);

    extern double degrees(double angle);

    extern Pair<double> normalize(Pair<double> vector);

    template <typename T>
    extern int sign(T n);

    template <typename T>
    extern int indexOf(std::vector<T> vector, T element);

    extern int random_integer(int min, int max);
}

#endif