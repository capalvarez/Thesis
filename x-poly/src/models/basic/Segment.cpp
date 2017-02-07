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
bool Segment<T>::contains(Point point, Point p1, Point p2) {
    return  ((point.getX()>=p1.getX() && point.getX()<=p2.getX()) || (point.getX()>=p2.getX() && point.getX()<=p1.getX())) &&
            ((point.getY()>=p1.getY() && point.getY()<=p2.getY()) || (point.getY()>=p2.getY() && point.getY()<=p1.getY())) &&
            std::abs(p1.getX()*(p2.getY()-point.getY()) + p2.getX()*(point.getY()-p1.getY()) + point.getX()*(p1.getY()-p2.getY()))<0.0001;
}

template class Segment<int>;
template class Segment<Point>;
