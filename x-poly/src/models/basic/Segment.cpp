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
std::string Segment<int>::getString() {
    return utilities::toString<double>(this->p1) + " " + utilities::toString<double>(this->p2);
}

template <>
std::string Segment<Point>::getString() {
    return this->p1.getString() + " " + this->p2.getString();
}


template class Segment<int>;
template class Segment<Point>;
