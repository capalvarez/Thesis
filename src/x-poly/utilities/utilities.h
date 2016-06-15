#ifndef THESIS_UTILITIES_H
#define THESIS_UTILITIES_H

#include <vector>

namespace utilities {

    extern void TrivialIndexVector(std::vector<int> index_vector, int n);

    template<class T>
    class DeleteVector;

    extern double radian(double angle);
}

#endif