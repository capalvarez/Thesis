#include <veamy/models/Element.h>
#include <veamy/models/Edge.h>
#include <veamy/physics/Material.h>
#include <veamy/matrix/quadrature/QuadraturePolygon.h>

Element::Element(ProblemConditions& conditions, Polygon p, UniqueList<Point>& points, DOFS& out) {
    std::vector<int> vertex = p.getPoints();
    int n = vertex.size();

    for(int i=0;i<n;i++){
        SegmentPair<int> pair(Segment<int>(vertex[(i-1+n)%n],vertex[i]), Segment<int>(vertex[i],vertex[(i+1)%n]));
        Pair<int> indexes = out.addDOF(conditions.constraints, points.getList(), vertex[i], pair);

        dofs.push_back(indexes.first);
        dofs.push_back(indexes.second);
    }

    std::vector<Point> pointVector = points.getList();
    initMatrix(out, pointVector, p, conditions);
}

void Element::initMatrix(DOFS d, std::vector<Point> points, Polygon p, ProblemConditions& conditions) {
    std::vector<int> polygonPoints = p.getPoints();
    int n = (int) polygonPoints.size();
    Point average = p.getAverageVertex(points);
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
        Point vertex = points[polygonPoints[vertex_id]];

        Edge prev (polygonPoints[(n+vertex_id-1)%n], polygonPoints[vertex_id]);
        Edge next (polygonPoints[vertex_id], polygonPoints[(n+vertex_id+1)%n]);

        Pair<double> prevNormal = prev.getNormal(polygonPoints,points);
        Pair<double> nextNormal = next.getNormal(polygonPoints,points);

        double prevLength = prev.getLength(points);
        double nextLength = next.getLength(points);

        double xDiff = vertex.getX() - average.getX();
        double yDiff = vertex.getY() - average.getY();

        double Qi_x = 1/(4*area)*(prevNormal.first*prevLength + nextNormal.first*nextLength);
        double Qi_y = 1/(4*area)*(prevNormal.second*prevLength + nextNormal.second*nextLength);

        Nr(2*vertex_id, 0) = 1;
        Nr(2*vertex_id, 2) = yDiff;
        Nr(2*vertex_id+1, 1) = 1;
        Nr(2*vertex_id+1, 2) = -xDiff;

        Wr(2*vertex_id, 0) = 1.0/n;
        Wr(2*vertex_id, 2) = Qi_y;
        Wr(2*vertex_id+1, 1) = 1.0/n;
        Wr(2*vertex_id+1, 2) = -Qi_x;

        Nc(2*vertex_id, 0) = xDiff;
        Nc(2*vertex_id, 2) = yDiff;
        Nc(2*vertex_id+1, 1) = yDiff;
        Nc(2*vertex_id+1, 2) = xDiff;

        Wc(2*vertex_id, 0) = 2*Qi_x;
        Wc(2*vertex_id, 2) = Qi_y;
        Wc(2*vertex_id+1, 1) = 2*Qi_y;
        Wc(2*vertex_id+1, 2) = Qi_x;
    }

    Eigen::MatrixXd Pr;
    Eigen::MatrixXd Pc;
    Eigen::MatrixXd Pp;
    Eigen::MatrixXd I;

    I = Eigen::MatrixXd::Identity(2*n, 2*n);

    Pr = Nr*(Wr.transpose());
    Pc = Nc*(Wc.transpose());

    Pp = Pc + Pr;

    Eigen::MatrixXd D = conditions.material.getMaterialMatrix();

    //TODO: Study this coefficient's influence
    double gamma = 1;
    double c = (Nc.transpose()*Nc).trace();
    double alphaS = area*conditions.material.trace()/c;
    Eigen::MatrixXd Se;
    Se = gamma*alphaS*I;

    this->K = area*Wc*D*Wc.transpose() + (I - Pp).transpose()*Se*(I - Pp);

    this->f = Eigen::VectorXd::Zero(dofs.size());
    NaturalConstraints natural = conditions.constraints.getNaturalConstraints();

    QuadraturePolygon polygon(p);

    for (int i = 0; i < dofs.size(); ++i) {
        this->f(i) = polygon.integrate(conditions.f, points) + natural.lineIntegral(points,p,i/2,dofs[i]);
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
        int globalI = out.get(this->dofs[i]).globalIndex();

        for (int j = 0; j < this->K.cols(); j++) {
            int globalJ = out.get(this->dofs[j]).globalIndex();

            Kglobal(globalI, globalJ) = Kglobal(globalI, globalJ) + this->K(i, j);
        }
    }
}

void Element::assembleF(DOFS out, Eigen::VectorXd &Fglobal) {
    for (int i = 0; i < this->K.rows(); i++) {
        int globalI = out.get(this->dofs[i]).globalIndex();

        Fglobal(globalI) = Fglobal(globalI) + this->f(i);
    }
}











