#ifndef THESIS_UTILITIES_H
#define THESIS_UTILITIES_H

#include <vector>
#include <iostream>

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

    template <typename T>
    extern std::string toString(T a);

    template <typename T>
    extern int indexOf(std::vector<T> vector, T element);
}

#endif