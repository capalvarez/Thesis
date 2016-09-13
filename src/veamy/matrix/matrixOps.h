#ifndef THESIS_MATRIXOPS_H
#define THESIS_MATRIXOPS_H


namespace matrixOps {
    void removeRow(Eigen::MatrixXd& matrix, int rowToRemove);
    void removeColumn(Eigen::MatrixXd& matrix, int colToRemove);
};


#endif
