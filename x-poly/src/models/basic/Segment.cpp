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
bool Segment<int>::intersects(std::vector<Point> points, Segment<Point> other) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    Point o1 = other.getFirst();
    Point o2 = other.getSecond();

    char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
                               float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
    {
        float s1_x, s1_y, s2_x, s2_y;
        s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
        s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

        float s, t;
        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
            // Collision detected
            if (i_x != NULL)
                *i_x = p0_x + (t * s1_x);
            if (i_y != NULL)
                *i_y = p0_y + (t * s1_y);
            return 1;
        }

        return 0; // No collision
    }
}


template class Segment<int>;
template class Segment<Point>;
