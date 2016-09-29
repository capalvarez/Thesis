#include <iostream>
#include <veamy/matrix/matrixOps.h>

namespace matrixOps {
    void removeRow(Eigen::MatrixXd& matrix, int rowToRemove){
        int numRows = matrix.rows()-1;
        int numCols = matrix.cols();

        if(rowToRemove<numRows){
            matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) =
                    matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);
        }

        matrix.conservativeResize(numRows,numCols);
    }

    void removeColumn(Eigen::MatrixXd& matrix, int colToRemove){
        int numRows = matrix.rows();
        int numCols = matrix.cols()-1;

        if(colToRemove<numCols){
            matrix.block(0,colToRemove,numRows,numCols-colToRemove) =
                    matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);
        }

        matrix.conservativeResize(numRows,numCols);
    }

    Eigen::MatrixXd getColumns(Eigen::MatrixXd& matrix, std::vector<int> cols){
        Eigen::MatrixXd newMatrix;
        newMatrix = Eigen::MatrixXd::Zero(matrix.rows(),cols.size());

        for (int i = 0; i < cols.size(); ++i) {
            newMatrix.col(i) = matrix.col(cols[i]);
        }

        return newMatrix;
    }

    void removeElement(Eigen::VectorXd& vector, int index){
        int numRows = vector.rows()-1;

        if(index<numRows){
            vector.segment(index,numRows-index) =
                    vector.segment(index+1,numRows-index);
        }

        vector.conservativeResize(numRows);
    }
}