#include <iostream>
#include <models/integration/IntegrationFunction.h>
#include "Element.h"

Element::Element(Polygon p, List<Point>& points, DOFS& out, int k, func_t f) {
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
    initMatrix(out, pointVector, weights, p, k, f);
}

void Element::initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, int k, func_t f) {
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

    //std::cout << B << std::endl << std::endl  << D << std::endl << std::endl;

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

    Eigen::MatrixXd H;
    H = Eigen::MatrixXd::Zero(b.nOfPolinomials(), b.nOfPolinomials());

    IntegrationPolygon polygon(p.getPoints(), points);

    for (int alpha=0;alpha<b.nOfPolinomials();++alpha){
        for (int beta = 0; beta < b.nOfPolinomials(); ++beta) {
            Pair<int> mAlpha = b.getPolinomial(alpha);
            Pair<int> mBeta = b.getPolinomial(beta);

            MaMbFunction* f = new MaMbFunction(mAlpha, mBeta, p);

            H(alpha,beta) = polygon.integrate(f, points);

            delete(f);
        }
    }

    std::cout << H << std::endl;

    if(k>1){
        Eigen::MatrixXd C;
        C = Eigen::MatrixXd::Zero(b.nOfPolinomials(), this->dofs.size());

        for (int alpha = 0; alpha < b.nOfPolinomials() - 2; ++alpha) {
            C(alpha, k*p.numberOfSides() - 1 + alpha) = p.getArea();
        }

        Eigen::MatrixXd Cfull = H*PiS;

        C.row(b.nOfPolinomials() - 2) = Cfull.row(b.nOfPolinomials() - 2);
        C.row(b.nOfPolinomials() - 1) = Cfull.row(b.nOfPolinomials() - 1);

        Eigen::MatrixXd PiZeroS;
        PiZeroS = H.inverse() * C;

        class LoadTerm : public IntegrationFunction{
        private:
            int i;
            int k;
            Polygon poly;
            Eigen::MatrixXd PiZS;
            func_t f;
        public:
            LoadTerm(int i, int k, Polygon p, func_t f, Eigen::MatrixXd PiZeroS){
                this->i = i;
                this->k = k;
                this->poly = p;
                this->f = f;
                this->PiZS = PiZeroS;
            }

            double call(double x, double y){
                double xFactor = ((x - poly.getCentroid().getX())/poly.getDiameter());
                double yFactor = ((y - poly.getCentroid().getY())/poly.getDiameter());

                BasePolinomials b(k);
                double PiSPhi = 0;

                for (int alpha = 0; alpha < b.nOfPolinomials(); ++alpha) {
                    Pair<int> a = b.getPolinomial(alpha);

                    PiSPhi += PiZS(alpha,i)*operations::power(xFactor,a.first)*operations::power(yFactor,a.second);
                }

                return f(x,y)*PiSPhi;
            }
        };

        this->f = Eigen::VectorXd::Zero(dofs.size());

        for (int i = 0; i < dofs.size(); ++i) {
            LoadTerm* l = new LoadTerm(i,k,p,f,PiZeroS);
            this->f(i) = polygon.integrate(l,points);

            delete(l);
        }
    }else{
        class LoadTerm: public IntegrationFunction{
        private:
            func_t f;
        public:
            LoadTerm(func_t f){
                this->f = f;
            }
            double call(double x, double y){
                return f(x,y);
            }
        };

        this->f = Eigen::VectorXd::Zero(dofs.size());
        LoadTerm* l = new LoadTerm(f);

        for (int i = 0; i < dofs.size(); ++i) {
            this->f(i) = polygon.integrate(l,points)/p.numberOfSides();
        }

        delete(l);
    }
}

Eigen::MatrixXd Element::getK() {
    return this->K;
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











