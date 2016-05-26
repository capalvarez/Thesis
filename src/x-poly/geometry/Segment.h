#include <vector>
#include "Point.h"

class Segment {
private:
    int p1;
    int p2;
public:
    Segment(int p1, int p2);
    ~Segment();

    int getFirst();
    int getSecond();
    bool operator==(Segment& other);
};



