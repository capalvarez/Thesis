#ifndef THESIS_MATRIXOPS_H
#define THESIS_MATRIXOPS_H

#include <veamy/lib/Eigen/Dense>

namespace matrixOps {
    Eigen::MatrixXd getColumns(Eigen::MatrixXd& matrix, std::vector<int> cols);
};


#endif


