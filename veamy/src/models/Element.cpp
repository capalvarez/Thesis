#include <veamy/models/Element.h>

Element::Element(ConstraintsContainer& constraints, Polygon p, List<Point>& points, DOFS& out, BodyForce* f) {
    std::vector<int> vertex = p.getPoints();
    int n = vertex.size();

    for(int i=0;i<n;i++){
        SegmentPair pair(Segment(vertex[(i-1+n)%n],vertex[i]), Segment(vertex[i],vertex[(i+1)%n]));
        Pair<int> indexes = out.addDOF(constraints, points.getList(), vertex[i], pair);

        dofs.push_back(indexes.first);
        dofs.push_back(indexes.second);
    }

    std::vector<Point> pointVector = points.getList();
    initMatrix(out, pointVector, p, f, constraints);
}

void Element::initMatrix(DOFS d, std::vector<Point> points, Polygon p, BodyForce* f,
                         ConstraintsContainer constraints) {
    std::vector<int> polygonPoints = p.getPoints();
    int n = (int) polygonPoints.size();
    Point average = p.getAverageVertex();
    double area = p.getArea();

    Eigen::MatrixXd Nr;
    Eigen::MatrixXd Wr;
    Eigen::MatrixXd Nc;
    Eigen::MatrixXd Wc;

    Nr = Eigen::MatrixXd::Zero(2*n, 3);
    Wr = Eigen::MatrixXd::Zero(2*n, 3);
    Nc = Eigen::MatrixXd::Zero(2*n, 3);
    Wc = Eigen::MatrixXd::Zero(2*n, 3);

    for(int vertex_id=0; vertex_id<n; vertex_id++){
        Point vertex = points[vertex_id];
        double xDiff = vertex.getX() - average.getX();
        double yDiff = vertex.getY() - average.getY();



        Vector Qi = 1/4*area*()


        Nr(2*vertex_id, 0) = 1;
        Nr(2*vertex_id, 2) = yDiff;
        Nr(2*vertex_id+1, 1) = 1;
        Nr(2*vertex_id+1, 2) = -xDiff;

        Wr(2*vertex_id, 0) = 1/n;
        Wr(2*vertex_id, 2) = ;
        Wr(2*vertex_id+1, 1) = 1/n;
        Wr(2*vertex_id+1, 2) = ;

        Nc(2*vertex_id, 0) = xDiff;
        Nc(2*vertex_id, 2) = yDiff;
        Nc(2*vertex_id+1, 1) = yDiff;
        Nc(2*vertex_id+1, 2) = xDiff;

        Wc(2*vertex_id, 0) = 1/n;
        Wc(2*vertex_id, 2) = ;
        Wc(2*vertex_id+1, 1) = 1/n;
        Wc(2*vertex_id+1, 2) = ;
    }


    Eigen::MatrixXd Pr;
    Eigen::MatrixXd Pc;
    Eigen::MatrixXd Pp;
    Eigen::MatrixXd I;

    I = Eigen::MatrixXd::Identity(2*n, 2*n);

    Pr = Nr*Wr.transpose();
    Pc = Nc*Wc.transpose();

    Pp = Pc + Pr;

    this->K = area*Wc*D*Wc.transpose() + (I - Pp).transpose()*(I - Pp);



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











