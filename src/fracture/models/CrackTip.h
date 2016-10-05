#ifndef THESIS_CRACKTIP_H
#define THESIS_CRACKTIP_H


#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>

class CrackTip {
private:
    double length;
    std::vector<Point> crackPath;
    Polygon container;
    std::vector<int> relatedDOFS;

    void addPointToPath(double angle);
public:
    CrackTip(double length);

};


#endif
