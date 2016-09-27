#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>

class Crack {
private:
    std::vector<Point> crack_path;
public:
    Crack();
    Crack(Point init, Point end);
    Crack(Point init, double angle, double length);

};


#endif
