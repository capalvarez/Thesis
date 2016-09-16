#ifndef THESIS_MATRIXOPS_H
#define THESIS_MATRIXOPS_H

#include <veamy/lib/Eigen/Dense>

namespace matrixOps {
    void removeRow(Eigen::MatrixXd& matrix, int rowToRemove);
    void removeColumn(Eigen::MatrixXd& matrix, int colToRemove);
    Eigen::MatrixXd getColumns(Eigen::MatrixXd& matrix, std::vector<int> cols);
    void removeElement(Eigen::VectorXd& vector, int index);
};


#endif
