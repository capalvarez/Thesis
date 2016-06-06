#include "Point.h"
#include "Segment.h"
#include <vector>

class Hole {
public:
    virtual Point getCenter() = 0;
    virtual void getSegments(std::vector<Segment> segments) = 0;
};

