#ifndef THESIS_POINTGENERATOR_H
#define THESIS_POINTGENERATOR_H

#include "models/basic/Point.h"
#include "models/polygon/Rectangle.h"
#include "Functor.h"
#include <vector>

class PointGenerator {
private:
    Functor* lX;
    Functor* lY;
public:
    PointGenerator(Functor* lX, Functor* lY);

    void generate(std::vector<Point>& vector, Rectangle box, int nX, int nY);
};

#endif
