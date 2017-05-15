#include <x-poly/models/polygon/Polygon.h>

Polygon::Polygon(std::vector<int>& points, std::vector<Point>& p) {
    if(isSelfIntersecting(p)){
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->points.assign(points.begin(), points.end());

    std::vector<Point> this_points;
    for (int i = 0; i < points.size(); i++) {
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
    calculateHash();
}

void Polygon::mutate(std::vector<Point> &p) {
    this->points.clear();
    xpoly_utilities::TrivialIndexVector(this->points,p.size());

    if(isSelfIntersecting(p)){
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    calculateHash();

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
    calculateHash();
}

void Polygon::mutate(std::vector<int> points, std::vector<Point> p) {
    if(isSelfIntersecting(p)){
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->points.assign(points.begin(), points.end());

    std::vector<Point> this_points;
    for (int i = 0; i < points.size(); i++) {
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
    calculateHash();
}

void Polygon::update(std::vector<Point> points) {
    this->area = calculateArea(points);
    this->centroid = calculateCentroid(points);

    std::vector<Point> this_points;
    for(int i=0;i<this->points.size();i++){
        this_points.push_back(points[this->points[i]]);
    }

    this->diameter = calculateDiameter(this_points);
}

Polygon::Polygon(std::vector<Point> &p) {
    if(isSelfIntersecting(p)){
        std::invalid_argument("Self intersecting polygons are not supported");
    }

    xpoly_utilities::TrivialIndexVector(this->points,p.size());

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
    calculateHash();
}

Polygon::Polygon() {}

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
        double distance = xpoly_utilities::norm (rotatingCalipers[i].first - rotatingCalipers[i].second);
        if(distance>max){
            max = distance;
        }
    }

    return max;
}

double Polygon::calculateArea(std::vector<Point>& p) {
    return geometry_functions::area(p,this->points);
}

void Polygon::changePointIndexes(std::vector<int> p) {
    this->points.insert(this->points.begin(), p.begin(), p.end());
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

void Polygon::getSegments(std::vector<IndexSegment>& segments) {
    int n = (int) this->points.size();

    for(int i=0;i<n; i++){
        IndexSegment s (this->points[i%n], this->points[(i+1)%n]);
        segments.push_back(s);
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

    if(oddNodes){
        return true;
    }

    return inEdges(p,point);
}

IndexSegment Polygon::containerEdge(std::vector<Point>& p, Point point){
    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    for(int i=0; i<segments.size(); i++){
        if(segments[i].contains(p,point)){
            return segments[i];
        }
    }

    return IndexSegment(-1, -1);
}

bool Polygon::inEdges(std::vector<Point>& p, Point point) {
    IndexSegment container = containerEdge(p, point);

    return container.getFirst()!= -1 && container.getSecond()!= -1;
}

bool Polygon::isConvex(std::vector<Point>& p) {
    int n = (int) this->points.size();

    double determinant = xpoly_utilities::orientation(p[0],p[1],p[2]);

    for(int i=1;i<n; i++){
        double newResult = xpoly_utilities::orientation(p[this->points[i]],p[this->points[(i+1)%n]],p[this->points[(i+2)%n]]);

        if(determinant*newResult<0){
            return false;
        }
    }

    return true;
}

std::vector<int> Polygon::getPoints() const{
    return this->points;
}

std::vector<int> &Polygon::getPoints() {
    return this->points;
}

int Polygon::numberOfSides() const{
    return (int) points.size();
}


bool Polygon::isClockwise(std::vector<Point> &p) {
    int n = (int) points.size();

    Point pI = p[points[0]];
    Point pI1 = p[points[n-1]];

    double sum = (pI.getX() - pI1.getX())*(pI.getY() + pI1.getY());

    for(int i=0; i<n-1; i++){
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
    std::string base = utilities::toString<double>(this->points[0]);

    for(int i=1;i<this->points.size();i++){
        base += " " + utilities::toString<double>(this->points[i]);
    }

    return base + " " + getCentroid().getString();
}

bool Polygon::isVertex(int index) {
    return std::find(points.begin(), points.end(), index) != points.end();
}

bool Polygon::isVertex(Point p, std::vector<Point> points, int &vertexIndex) {
    for (int i: this->points){
        if(points[i]==p){
            vertexIndex = i;
            return true;
        }
    }

    return false;
}

void Polygon::calculateHash() {
    std::size_t hash = 0;

    for (int i = 0; i < points.size(); ++i) {
        hash+= utilities::hash32(points[i]);
    }

    this->hash = hash;
}

void Polygon::fixCCW(std::vector<Point> p) {
    if(isClockwise(p)){
        std::reverse(this->points.begin(), this->points.end());
        this->area = -this->area;
    }
}

std::vector<Point> Polygon::getPoints(std::vector<Point> p) {
    std::vector<Point> returnPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        returnPoints.push_back(p[this->points[i]]);
    }

    return returnPoints;
}

Pair<int> Polygon::commonEdgesBorder(Polygon p, std::vector<Point> points, bool &special) {
    std::map<int,int> thisPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        thisPoints[this->points[i]] = 1;
    }

    int j,k, n = p.numberOfSides();
    std::vector<int> poly_points = p.getPoints();
    int nP = p.numberOfSides();

    for (j = 0; j < nP; ++j) {
        auto search = thisPoints.find(poly_points[j]);

        if(search != thisPoints.end() && (thisPoints.find(poly_points[(j-1+nP)%nP])!=thisPoints.end() ||
                thisPoints.find(poly_points[(j+1)%nP])!=thisPoints.end())) {
            break;
        }
    }

    k = (j + 1)%n;
    int i = 0;
    bool last = true;
    std::vector<int> border;

    while (i<n){
        bool now = thisPoints[poly_points[k]]==0;
        bool next = thisPoints[poly_points[(k+1)%n]]==1;

        if(now && last){
            if(thisPoints[poly_points[(n+k-2)%n]]==1){
                border.push_back(poly_points[(k-1+n)%n]);
            }
        }

        if(!now && !last && next){
            border.push_back(poly_points[k]);
        }

        last = thisPoints[poly_points[k]]==1;
        k = (k+1)%n;
        i++;
    }

    if(border.size()==0){
        special = true;
        if(this->containsPoint(points, p.getCentroid())){
            //polygon is inside, do something
            return Pair<int>(-1,-1);
        }else{
            std::vector<IndexSegment> s;
            p.getSegments(s);

            return this->segmentNotContained(s);
        }
    }


    return Pair<int>(border[0], border.back());
}

bool Polygon::operator<(const Polygon &other) const {
    return this->hash<other.hash;
}

void Polygon::replace_segment(IndexSegment seg, std::vector<IndexSegment> segs, std::vector<Point> points) {
    if(segs.size()==1 && seg == segs[0])
        return;

    std::vector<int> orderedSegments;
    IndexSegment segment = segs[segs.size()-1];

    if(segment.isCCW(points,this->centroid)){
        orderedSegments.push_back(segment.getFirst());
        orderedSegments.push_back(segment.getSecond());
    }else{
        orderedSegments.push_back(segment.getSecond());
        orderedSegments.push_back(segment.getFirst());
    }

    segs.pop_back();
    int i = segs.size()-1;

    while(segs.size()!=0) {
        if(i<0){
            i = segs.size()-1;
        }

        segment = segs[i];
        segment.orderCCW(points,this->centroid);

        if(segment.isVertex(orderedSegments.front())){
            orderedSegments.insert(orderedSegments.begin(), segment.getFirst());
            segs.erase(segs.begin()+i);
            i--;
            continue;
        }

        if(segment.isVertex(orderedSegments.back())){
            orderedSegments.push_back(segment.getSecond());
            segs.erase(segs.begin()+i);
            i--;
            continue;
        }

        i--;
    }

    seg.orderCCW(points, this->getCentroid());
    int indexOfStart = utilities::indexOf(this->points, seg.getFirst());

    this->points.insert(this->points.begin()+indexOfStart+1, orderedSegments.begin()+1, orderedSegments.end()-1);
    this->mutate(this->points,points);
}

bool Polygon::isSelfIntersecting(std::vector<Point> points) {
    std::vector<IndexSegment> segments;
    this->getSegments(segments);
    int n = segments.size();
    Point intersection;

    for (int i = 0; i < n; ++i) {
        IndexSegment s = segments[i];

        for (int j = 0; j < n; ++j) {
            if(i==j || j==(i-1+n)%n || j==(i+1)%n){
                continue;
            }

            if(s.intersection(points,segments[j],intersection)){
                return true;
            }
        }
    }
    return false;
}

bool Polygon::intersectsSegment(PointSegment segment, std::vector<Point> points) {
    Point p;
    std::vector<IndexSegment> poly_segs;
    this->getSegments(poly_segs);

    for (IndexSegment seg: poly_segs) {
        if(seg.intersection(points, segment,p)){
            return true;
        }
    }

    return false;
}

std::vector<IndexSegment> Polygon::getAdjacentEdges(int i) {
    std::vector<IndexSegment> segs;
    int index = utilities::indexOf(this->points, i);
    int n = this->numberOfSides();

    if (index != -1){
        segs.push_back(IndexSegment(this->points[(n+index-1)%n], this->points[index]));
        segs.push_back(IndexSegment(this->points[index], this->points[(n+index+1)%n]));
    }

    return segs;
}

int Polygon::getPoint(int i) {
    return this->points[i];
}

Pair<int> Polygon::segmentNotContained(std::vector<IndexSegment> s) {
    for (IndexSegment segment: s) {
        if(!containsEdge(segment)){
            return Pair<int>(segment.getFirst(), segment.getSecond());
        }
    }
    return Pair<int>(-1,-1);
}

bool Polygon::containsEdge(IndexSegment s) {
    int n = this->numberOfSides();

    int i = utilities::indexOf(this->points, s.getFirst());
    int j = utilities::indexOf(this->points, s.getSecond());

    return i!=-1 && j!=-1 && (std::abs(i-j)==1 || std::abs(i-j)==(n-1));
}

void Polygon::insertOnSegment(IndexSegment segment, int point) {
    std::vector<int> points = {point};

    insertOnSegment(segment, points);
}

void Polygon::insertOnSegment(IndexSegment segment, std::vector<int> point) {
    int n = this->numberOfSides();

    int i = utilities::indexOf(this->points, segment.getFirst());
    int j = utilities::indexOf(this->points, segment.getSecond());

    if(i!=-1 && j!=-1 && (std::abs(i-j)==1 || std::abs(i-j)==(n-1))){
        if(i==n-1){
            this->points.insert(this->points.end(), point.begin(), point.end());
        }else{
            this->points.insert(this->points.begin()+i, point.begin(), point.end());
        }

    }
}

bool Polygon::isValidPolygon() {
    UniqueList<int> vertices;
    vertices.push_list(this->points);

    return vertices.size()>2 && this->area>10e-5;
}

IndexSegment Polygon::getIntersectedSegment(PointSegment direction, Point &intersection, std::vector<Point> points) {
    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    for (IndexSegment s: segments) {
        bool intersects = s.intersection(points, direction, intersection);

        if(intersects){
            return s;
        }
    }

    return IndexSegment();
}

int Polygon::getVertex(int p1, int p2) {
    return isVertex(p1)? p1 : p2;
}
