#include <x-poly/models/basic/IndexSegment.h>

IndexSegment::IndexSegment(int i1, int i2) : Segment<int>(i1, i2) {}

IndexSegment::IndexSegment() : Segment<int>(){}

bool IndexSegment::isBoundary(std::vector<Point> p) {
    return p[this->p1].isInBoundary() && p[this->p2].isInBoundary();
}

bool IndexSegment::contains(std::vector<Point> &p, Point point) {
    return Segment::contains(point,p[this->p1],p[this->p2]);
}

bool IndexSegment::contains(std::vector<Point> p, IndexSegment s) {
    return this->contains(p, p[s.getFirst()]) && this->contains(p, p[s.getSecond()]);
}

Point IndexSegment::middlePoint(std::vector<Point> p) {
    return Point((p[this->p1].getX() + p[this->p2].getX())/2, (p[this->p1].getY() + p[this->p2].getY())/2);
}

bool IndexSegment::intersection(std::vector<Point> points, PointSegment other, Point &inter) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    Point o1 = other.getFirst();
    Point o2 = other.getSecond();

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p2.getX() - p1.getX();     s1_y = p2.getY() - p1.getY();
    s2_x = o2.getX() - o1.getX();     s2_y = o2.getY() - o1.getY();

    double s, t;
    s = (-s1_y * (p1.getX() - o1.getX()) + s1_x * (p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p1.getY() - o1.getY()) - s2_y * (p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
        double i_x = p1.getX() + (t * s1_x);
        double i_y = p1.getY() + (t * s1_y);

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

void IndexSegment::orderCCW(std::vector<Point> points, Point center) {
    if(!this->isCCW(points, center)){
        int tmp = this->p1;
        this->p1 = this->p2;
        this->p2 = tmp;
    }
}

bool IndexSegment::isCCW(std::vector<Point> points, Point center) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    return xpoly_utilities::orientation(p1,p2,center)>0;
}

std::string IndexSegment::getString() const {
    return utilities::toString<double>(this->getFirst()) + " " + utilities::toString<double>(this->getSecond());
}

bool IndexSegment::operator==(const IndexSegment& other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

bool IndexSegment::operator<(const IndexSegment &other) const {
    if(this->p1==other.p1){
        return this->p2<other.p2;
    }

    return this->p1<other.p1;
}
