#include <iostream>
#include "Element.h"

Element::Element(Polygon p, List<Point>& points, DOFS& out, int k) {
    std::vector<int> vertex = p.getPoints();

    for(int i=0;i<vertex.size();i++){
        dofs.push_back(out.addVertexDOF(vertex[i]));
    }

    std::vector<double> quadrature;
    std::vector<double> weights;
    lobatto::lobatto_set(k+1,quadrature,weights);

    for(int vertex_id=0; vertex_id<vertex.size(); vertex_id++) {
        Point p1 = points.get(vertex[vertex_id]);
        Point p2 = points.get(vertex[(vertex_id + 1)%vertex.size()]);

        for (int l = 1; l < quadrature.size() - 1; l++) {
            double x = p1.getX() + (p2.getX() - p1.getX()) * quadrature[l];
            double y = p1.getY() + (p2.getY() - p1.getY()) * quadrature[l];

            Point newPoint(x, y);
            int index = points.push_back(newPoint);

            dofs.push_back(out.addEdgeDOF(index));
        }
    }

    BasePolinomials innerBase(k-2);
    for(int l=0;l<innerBase.nOfPolinomials();l++){
        dofs.push_back(out.addInnerDOF(innerBase.getPolinomial(l)));
    }

    std::vector<Point> pointVector = points.getList();
    initMatrix(out, pointVector, weights, p, k);
}

void Element::initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, int k) {
    BasePolinomials b(k);

    Eigen::MatrixXd D;
    Eigen::MatrixXd B;

    D = Eigen::MatrixXd::Zero(dofs.size(), b.nOfPolinomials());
    D.col(0).setOnes();

    for(int dof_id=0; dof_id<dofs.size(); dof_id++){
        for(int poly_id=1; poly_id<b.nOfPolinomials(); poly_id++){
            Pair<int> coefficients = b.getPolinomial(poly_id);

            D(dof_id,poly_id) = d.get(dofs[dof_id])->getValue(points, coefficients, p);
        }
    }

    B = Eigen::MatrixXd::Zero(b.nOfPolinomials(), dofs.size());

    if(k==1){
        B.row(0).setOnes();
        B.row(0) = B.row(0)*(1/(double)p.numberOfSides());
    }else{
        B(0,dofs.size()-1) = 1;
    }

    for(int poly_id=1;poly_id<b.nOfPolinomials();poly_id++){
        Pair<int> poly = b.getPolinomial(poly_id);

        for(int local=0;local<dofs.size();local++){
            B(poly_id,local) = d.get(dofs[local])->lineIntegral(local,k,p,weight,points,poly) +
                    d.get(dofs[local])->laplacianIntegral(poly,p);
        }
    }

    std::cout << B << std::endl << std::endl  << D << std::endl << std::endl;

    Eigen::MatrixXd G;
    Eigen::MatrixXd PiS;
    Eigen::MatrixXd Pi;
    Eigen::MatrixXd I;

    I = Eigen::MatrixXd::Identity(dofs.size(), dofs.size());
    G = B*D;
    PiS = G.inverse()*B;
    Pi = D*PiS;

    G.row(0).setZero();

    this->K = PiS.transpose()*G*PiS + (I-Pi).transpose()*(I-Pi);
}

Eigen::MatrixXd Element::getK() {
    return this->K;
}

void Element::initVector() {

}

Eigen::VectorXd Element::getF() {
    return this->f;
}

void Element::assembleK(DOFS out, Eigen::MatrixXd& Kglobal) {
    for (int i = 0; i < this->K.rows(); i++) {
        int globalI = out.get(this->dofs[i])->globalIndex();

        for (int j = 0; j < this->K.cols(); j++) {
            int globalJ = out.get(this->dofs[j])->globalIndex();

            Kglobal(globalI, globalJ) = Kglobal(globalI, globalJ) + this->K(i, j);
        }
    }
}

void Element::assembleF(DOFS out, Eigen::VectorXd &Fglobal) {
    for (int i = 0; i < this->K.rows(); i++) {
        int globalI = out.get(this->dofs[i])->globalIndex();

        Fglobal(globalI) = Fglobal(globalI) + this->f(i);
    }
}











