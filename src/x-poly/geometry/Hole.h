#ifndef THESIS_HOLE_H
#define THESIS_HOLE_H

#include "Point.h"

class Hole {
private:
    Point center;
public:
    Hole(Point center);
    ~Hole();

    Point getCenter();
};


#endif //THESIS_HOLE_H
