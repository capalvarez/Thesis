#ifndef THESIS_UTILITIES_H
#define THESIS_UTILITIES_H

#include <vector>

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
}

#endif