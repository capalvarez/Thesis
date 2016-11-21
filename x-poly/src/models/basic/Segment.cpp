#include <x-poly/models/basic/Segment.h>


template <class T>
Segment<T>::Segment(T p1, T p2) {
    this->p1 = p1;
    this->p2 = p2;
}

template <class T>
Segment<T>::Segment() {}

template <class T>
Segment<T>::~Segment() {}

template <class T>
T Segment<T>::getFirst() const{
    return this->p1;
}

template <class T>
T Segment<T>::getSecond() const{
    return this->p2;
}

template <class T>
bool Segment<T>::operator==(const Segment<T> other) const{
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

template <>
bool Segment<int>::contains(std::vector<Point>& p, Point point) {
    Point p1 = p[this->p1];
    Point p2 = p[this->p2];

    return  ((point.getX()>=p1.getX() && point.getX()<=p2.getX()) || (point.getX()>=p2.getX() && point.getX()<=p1.getX())) &&
            ((point.getY()>=p1.getY() && point.getY()<=p2.getY()) || (point.getY()>=p2.getY() && point.getY()<=p1.getY())) &&
            std::abs(p1.getX()*(p2.getY()-point.getY()) + p2.getX()*(point.getY()-p1.getY()) + point.getX()*(p1.getY()-p2.getY()))<0.0001;
}

template <>
bool Segment<Point>::contains(std::vector<Point>& p, Point point) {
    Point p1 = this->p1;
    Point p2 = this->p2;

    return  ((point.getX()>=p1.getX() && point.getX()<=p2.getX()) || (point.getX()>=p2.getX() && point.getX()<=p1.getX())) &&
            ((point.getY()>=p1.getY() && point.getY()<=p2.getY()) || (point.getY()>=p2.getY() && point.getY()<=p1.getY())) &&
            std::abs(p1.getX()*(p2.getY()-point.getY()) + p2.getX()*(point.getY()-p1.getY()) + point.getX()*(p1.getY()-p2.getY()))<0.0001;
}

template <>
Point Segment<int>::middlePoint(std::vector<Point> p) {
    return Point((p[this->p1].getX() + p[this->p2].getX())/2, (p[this->p1].getY() + p[this->p2].getY())/2);
}

template <>
Point Segment<Point>::middlePoint(std::vector<Point> p) {
    return Point((this->p1.getX() + this->p2.getX())/2, (this->p1.getY() + this->p2.getY())/2);
}

template <>
std::string Segment<int>::getString() const{
    return string_utils::toString<double>(this->getFirst()) + " " + string_utils::toString<double>(this->getSecond());
}

template <>
std::string Segment<Point>::getString() const{
    return this->getFirst().getString() + " " + this->getSecond().getString();
}

template <>
bool Segment<int>::contains(std::vector<Point> p, Segment<int> s) {
    return this->contains(p, p[s.getFirst()]) && this->contains(p, p[s.getSecond()]);
}

template <>
bool Segment<int>::isBoundary(std::vector<Point> p) {
    return p[this->p1].isInBoundary() && p[this->p2].isInBoundary();
}

template <>
bool Segment<Point>::isBoundary(std::vector<Point> p) {
    return this->p1.isInBoundary() && this->p2.isInBoundary();
}

template <>
bool Segment<int>::intersection(std::vector<Point> points, Segment<Point> other, Point &inter) {
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

template <>
bool Segment<int>::isCCW(std::vector<Point> points, Point center) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    double z = (p2.getX()-center.getX())*(p1.getY()-center.getY())-(p2.getY()-center.getY())*(p1.getX()-center.getX());

    return z>0;
}

template <>
void Segment<int>::orderCCW(std::vector<Point> points, Point center) {
    if(this->isCCW(points, center)){
        int tmp = this->p1;
        this->p1 = this->p2;
        this->p2 = tmp;
    }
}

template <>
double Segment<int>::cartesianAngle(std::vector<Point> points) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    double dY = p2.getY() - p1.getY();
    double dX = p2.getX() - p1.getX();

    return utilities::degrees(atan2(dY, dX));
}

template <>
double Segment<Point>::cartesianAngle(std::vector<Point> points) {
    Point p1 = this->p1;
    Point p2 = this->p2;

    double dY = p2.getY() - p1.getY();
    double dX = p2.getX() - p1.getX();

    return utilities::degrees(atan2(dY, dX));
}

template <>
double Segment<Point>::length() {
    return std::sqrt(std::pow(this->p1.getX() - this->p2.getX(), 2) + std::pow(this->p1.getY() - this->p2.getY(),2));
}


template class Segment<int>;
template class Segment<Point>;
