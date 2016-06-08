#ifndef THESIS_UTILITIES_H
#define THESIS_UTILITIES_H

#include <sstream>
#include <vector>

namespace utilities {
    template <typename T>
    std::string ToString(T val);

    void TrivialIndexVector(std::vector<int> index_vector, int n);

    template<class T>
    class DeleteVector;
}

#endif