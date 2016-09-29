#ifndef THESIS_GAUSSQUADRATURE_H
#define THESIS_GAUSSQUADRATURE_H

#include <x-poly/models/basic/Point.h>
#include <vector>

namespace gauss {
    extern  void gaussQuadrature(int order, std::vector<Point>& points, std::vector<double>& weight);
}


#endif 
