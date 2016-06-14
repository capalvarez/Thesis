#ifndef THESIS_POINTGENERATOR_H
#define THESIS_POINTGENERATOR_H

#include "models/basic/Point.h"
#include "models/polygon/Rectangle.h"
#include <functional>
#include <vector>

class PointGenerator {
private:
    std::function<double(double)> lX;
    std::function<double(double)> lY;
public:
    PointGenerator(std::function<double(double)> lX, std::function<double(double)> lY);

    void generate(std::vector<Point>& vector, Rectangle box, int nX, int nY);
};

#endif
