#include <algorithm>
#include <x-poly/models/polygon/Polygon.h>
#include <map>
#include <include/x-poly/utilities/Pair.h>


Polygon::Polygon(std::vector<int>& points, std::vector<Point>& p) {
    this->points.assign(points.begin(), points.end());

    std::vector<Point> this_points;
    for (int i = 0; i < points.size(); i++) {
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
}

void Polygon::mutate(std::vector<Point> &p) {
    this->points.clear();
    utilities::TrivialIndexVector(this->points,p.size());
    calculateHash();

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
}

Polygon::Polygon(std::vector<Point> &p) {
    utilities::TrivialIndexVector(this->points,p.size());

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
    calculateHash();
}


Polygon::Polygon() {

}

Polygon::Polygon(const Polygon &obj) {
    this->area = obj.area;
    this->diameter = obj.diameter;
    this->centroid = obj.centroid;

    this->points.assign(obj.points.begin(), obj.points.end());
    calculateHash();
}

double Polygon::calculateDiameter(std::vector<Point>& p) {
    std::vector<std::pair<Point,Point> > rotatingCalipers = convex::rotatingCalipers(p);
    double max = -1;

    for(int i=0;i<rotatingCalipers.size();i++){
        double distance = (rotatingCalipers[i].first - rotatingCalipers[i].second).norm();
        if(distance>max){
            max = distance;
        }
    }

    return max;
}

double Polygon::calculateArea(std::vector<Point>& p) {
    return geometry_functions::area(p,this->points);
}

double Polygon::getArea(){
    return this->area;
}

double Polygon::getDiameter() {
    return this->diameter;
}

Point Polygon::getCentroid() {
   return this->centroid;
}

double Polygon::signedArea(std::vector<Point>& p) {
    double area = 0;
    int n = (int) this->points.size();

    for(int i=0;i<n;i++){
        area += p[points[i]].getX()*p[points[(i+1)%n]].getY() - p[points[(i+1)%n]].getX()*p[points[i]].getY();
    }

    return 0.5*area;
}

void Polygon::getSegments(std::vector<Segment<int>>& segments) {
    int n = (int) this->points.size();

    for(int i=0;i<n; i++){
        Segment<int> s (this->points[i%n], this->points[(i+1)%n]);
        segments.push_back(s);
    }
}

void Polygon::getSegments(std::vector<Segment<int>> &segments, int offset) {
    int n = (int) this->points.size();

    for(int i=0;i<n; i++){
        segments.push_back(Segment<int>(this->points[i%n] + offset , this->points[(i+1)%n] + offset));
    }
}

Point Polygon::calculateCentroid(std::vector<Point>& p) {
    int n = this->points.size();
    double partial_x = 0;
    double partial_y = 0;

    for(int i=0;i<n;i++){
        Point pi = p[points[i]];
        Point pi1 = p[points[(i+1)%n]];

        partial_x += (pi.getX() + pi1.getX())*(pi.getX()*pi1.getY() - pi1.getX()*pi.getY());
        partial_y += (pi.getY() + pi1.getY())*(pi.getX()*pi1.getY() - pi1.getX()*pi.getY());
    }

    double A = this->signedArea(p);
    double cX = partial_x/(6*A);
    double cY = partial_y/(6*A);

    return Point (cX,cY);
}

bool Polygon::containsPoint(std::vector<Point>& p, Point point) {
    int j = points.size() - 1 ;
    bool oddNodes = false;

    for (int i=0; i<points.size(); i++) {
        Point pI = p[points[i]];
        Point pJ = p[points[j]];

        if (pI.getY()<=point.getY() && pJ.getY()>point.getY()
            || pJ.getY()<=point.getY() && pI.getY()>point.getY()) {

            if (pI.getX() + (point.getY()-pI.getY())/(pJ.getY()-pI.getY())*(pJ.getX()-pI.getX())<point.getX()){
                oddNodes=!oddNodes;
            }
        }
        j = i;
    }

    return oddNodes || inEdges(p,point);
}

Segment<int> Polygon::containerEdge(std::vector<Point>& p, Point point){
    std::vector<Segment<int>> segments;
    this->getSegments(segments);

    for(int i=0; i<segments.size(); i++){
        if(segments[i].contains(p,point)){
            return segments[i];
        }
    }

    return Segment<int>(-1, -1);
}

bool Polygon::inEdges(std::vector<Point>& p, Point point) {
    Segment<int> container = containerEdge(p, point);

    return container.getFirst()!= -1 && container.getSecond()!= -1;
}

bool Polygon::isConvex(std::vector<Point>& p) {
    int n = (int) this->points.size();

    double determinant = convex::orientation(p[0],p[1],p[2]);

    for(int i=1;i<n; i++){
        double newResult = convex::orientation(p[this->points[i]],p[this->points[(i+1)%n]],p[this->points[(i+2)%n]]);

        if(determinant*newResult<0){
            return false;
        }
    }

    return true;
}

std::vector<int> Polygon::getPoints() const{
    return this->points;
}


int Polygon::numberOfSides() {
    return (int) points.size();
}


bool Polygon::isClockwise(std::vector<Point> &p) {
    int n = (int) points.size();

    Point pI = p[points[0]];
    Point pI1 = p[points[n-1]];

    double sum = (pI.getX() - pI1.getX())*(pI.getY() + pI1.getY());

    for(int i=0; i<n; i++){
        pI1 = p[points[(i+1)%n]];
        pI = p[points[i]];

        sum += (pI1.getX() - pI.getX())*(pI1.getY() + pI.getY());
    }

    return sum>0;
}

bool Polygon::operator==(const Polygon &other) const{
    return std::is_permutation(this->points.begin(), this->points.end(), other.getPoints().begin());
}

std::string Polygon::getString() {
    std::string base = string_utils::toString<double>(this->points[0]);

    for(int i=1;i<this->points.size();i++){
        base += " " + string_utils::toString<double>(this->points[i]);
    }

    return base + " " + getCentroid().getString();
}

bool Polygon::containsEdge(Segment<int> s) {
    return isVertex(s.getFirst()) && isVertex(s.getSecond());
}

bool Polygon::isVertex(int index) {
    return std::find(points.begin(), points.end(), index) != points.end();
}

Point Polygon::getAverageVertex(std::vector<Point> p) {
    double x = 0;
    double y = 0;

    for (int i = 0; i < this->points.size(); ++i) {
        x += p[this->points[i]].getX();
        y += p[this->points[i]].getY();
    }

    return Point(x/this->numberOfSides(), y/this->numberOfSides());
}

void Polygon::calculateHash() {
    std::size_t hash = 0;

    for (int i = 0; i < points.size(); ++i) {
        hash+= std::hash<int>()(points[i]);
    }

    this->hash = hash;
}

void Polygon::fixCCW(std::vector<Point> p) {
    if(isClockwise(p)){
        std::reverse(this->points.begin(), this->points.end());
    }
}

std::vector<Point> Polygon::getPoints(std::vector<Point> p) {
    std::vector<Point> returnPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        returnPoints.push_back(p[this->points[i]]);
    }

    return returnPoints;
}

Pair<int> Polygon::commonEdgesBorder(Polygon p) {
    std::map<int,int> thisPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        thisPoints[this->points[i]] = 1;
    }

    int j,k, n = p.numberOfSides();
    std::vector<int> poly_points = p.getPoints();

    for (j = 0; j < poly_points.size(); ++j) {
        auto search = thisPoints.find(poly_points[j]);

        if(search != thisPoints.end()) {
            break;
        }
    }

    k = (j + 1)%n;
    int i = 0;
    bool last = true;
    std::vector<int> border;

    while (i<n+1){
        bool now = thisPoints[poly_points[k]]==0;

        if(now && last){
            border.push_back(poly_points[(k-1+n)%n]);
        }

        if(!now && !last){
            border.push_back(poly_points[k]);
        }

        last = thisPoints[poly_points[k]]==1;
        k = (k+1)%n;
        i++;
    }

    return Pair<int>(border[0], border[1]);
}

bool Polygon::isPoint(int index) {
    return std::find(this->points.begin(), this->points.end(), index)!=this->points.end();
}



