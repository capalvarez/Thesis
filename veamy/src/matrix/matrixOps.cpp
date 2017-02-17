#include <iostream>
#include <veamy/matrix/matrixOps.h>

namespace matrixOps {
    Eigen::MatrixXd getColumns(Eigen::MatrixXd& matrix, std::vector<int> cols){
        Eigen::MatrixXd newMatrix;
        newMatrix = Eigen::MatrixXd::Zero(matrix.rows(),cols.size());

        for (int i = 0; i < cols.size(); ++i) {
            newMatrix.col(i) = matrix.col(cols[i]);
        }

        return newMatrix;
    }
}