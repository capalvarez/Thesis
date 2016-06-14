#include "Rectangle.h"


Rectangle::Rectangle(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;
}

double Rectangle::getWidth() {
    return std::abs(p1.getX() - p2.getX());
}

double Rectangle::getHeight() {
    return std::abs(p1.getY() - p2.getY());
}

double Rectangle::xMin() {
    return std::min(p1.getX(), p2.getX());
}

double Rectangle::yMin() {
    return std::min(p1.getY(), p2.getY());
}

