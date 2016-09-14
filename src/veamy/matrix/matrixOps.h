#ifndef THESIS_MATRIXOPS_H
#define THESIS_MATRIXOPS_H

#include <Eigen/Dense>

namespace matrixOps {
    void removeRow(Eigen::MatrixXd& matrix, int rowToRemove);
    void removeColumn(Eigen::MatrixXd& matrix, int colToRemove);
    Eigen::MatrixXd getColumns(Eigen::MatrixXd& matrix, std::vector<int> cols);
};


#endif
