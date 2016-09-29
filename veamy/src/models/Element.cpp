#include <veamy/models/Element.h>

Element::Element(ConstraintsContainer& constraints, Polygon p, List<Point>& points, DOFS& out, int k, BodyForce* f) {
    std::vector<int> vertex = p.getPoints();
    int n = vertex.size();

    for(int i=0;i<n;i++){
        SegmentPair pair(Segment(vertex[(i-1+n)%n],vertex[i]), Segment(vertex[i],vertex[(i+1)%n]));
        Pair<int> indexes = out.addVertexDOF(constraints, points.getList(), vertex[i], pair);

        dofs.push_back(indexes.first);
        dofs.push_back(indexes.second);
    }

    std::vector<double> quadrature;
    std::vector<double> weights;
    lobatto::lobatto_set(k+1,quadrature,weights);

    for(int vertex_id=0; vertex_id<n; vertex_id++) {
        Segment s (vertex[vertex_id], vertex[(vertex_id + 1)%n]);
        SegmentPair pair(s);

        Point p1 = points.get(s.getFirst());
        Point p2 = points.get(s.getSecond());

        for (int l = 1; l < quadrature.size() - 1; l++) {
            double x = p1.getX() + (p2.getX() - p1.getX()) * quadrature[l];
            double y = p1.getY() + (p2.getY() - p1.getY()) * quadrature[l];

            Point newPoint(x, y);
            int index = points.push_back(newPoint);

            Pair<int> indexes = out.addEdgeDOF(constraints, points.getList(), index, pair);

            dofs.push_back(indexes.first);
            dofs.push_back(indexes.second);
        }
    }

    BasePolinomials innerBase(k-2);
    for(int l=0;l<innerBase.nOfPolinomials();l++){
        Pair<int> indexes = out.addInnerDOF(innerBase.getPolinomial(l));

        dofs.push_back(indexes.first);
        dofs.push_back(indexes.second);
    }

    std::vector<Point> pointVector = points.getList();
    initMatrix(out, pointVector, weights, p, k, f, constraints);
}

void Element::initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, int k, BodyForce* f,
                         ConstraintsContainer constraints) {
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
        B(0,dofs.size()-2) = 1;
        B(0,dofs.size()-1) = 1;
    }

    for(int poly_id=1;poly_id<b.nOfPolinomials();poly_id++){
        Pair<int> poly = b.getPolinomial(poly_id);

        for(int local=0;local<dofs.size();local++){
            B(poly_id,local) = d.get(dofs[local])->lineIntegral(local,this->dofs,d.getDOFS().getList(),k,p,weight,points,poly) +
                    d.get(dofs[local])->laplacianIntegral(poly,p);
        }
    }

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

    BasePolinomials bK_2(k-2);
    Eigen::MatrixXd C;
    C = Eigen::MatrixXd::Zero(b.nOfPolinomials(), this->dofs.size());

    for (int alpha = 0; alpha < bK_2.nOfPolinomials(); ++alpha) {
        C(alpha, k*p.numberOfSides() - 1 + alpha) = p.getArea();
    }

    Eigen::MatrixXd Cfull = H*PiS;

    for (int i = bK_2.nOfPolinomials(); i < b.nOfPolinomials() ; ++i) {
        C.row(i) = Cfull.row(i);
    }

    Eigen::MatrixXd PiZeroS;
    PiZeroS = H.inverse() * C;


    //TODO: Reuse code here, somehow
    class LoadTerm : public IntegrationFunction {
    private:
        int i;
        int k;
        Polygon poly;
        Eigen::MatrixXd PiZS;
        BodyForce* f;
    public:
        LoadTerm(int i, int k, Polygon p, BodyForce* f, Eigen::MatrixXd PiZeroS) {
            this->i = i;
            this->k = k;
            this->poly = p;
            this->f = f;
            this->PiZS = PiZeroS;
        }

        double call(double x, double y) {
            double xFactor = ((x - poly.getCentroid().getX()) / poly.getDiameter());
            double yFactor = ((y - poly.getCentroid().getY()) / poly.getDiameter());

            BasePolinomials b(k);
            double PiSPhi = 0;

            for (int alpha = 0; alpha < b.nOfPolinomials(); ++alpha) {
                Pair<int> a = b.getPolinomial(alpha);

                PiSPhi += PiZS(alpha, i) * operations::power(xFactor, a.first) * operations::power(yFactor, a.second);
            }

            return f->apply(x, y) * PiSPhi;
        }
    };

    this->f = Eigen::VectorXd::Zero(dofs.size());
    NaturalConstraints natural = constraints.getNaturalConstraints();

    for (int i = 0; i < dofs.size(); ++i) {
        LoadTerm *l = new LoadTerm(i, k, p, f, PiZeroS);
        this->f(i) = polygon.integrate(l, points) + natural.lineIntegral(points,p,dofs[i],i,k,PiZeroS);

        delete (l);
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











