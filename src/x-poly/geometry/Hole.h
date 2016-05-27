#include "Point.h"

class Hole {
private:
    Point center;
public:
    Hole(Point center);
    ~Hole();

    Point getCenter();
};

