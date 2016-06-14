#include "PointGenerator.h"


PointGenerator::PointGenerator(std::function<double(double)> lX, std::function<double(double)> lY) {
    this->lX = lX;
    this->lY = lY;
}

void PointGenerator::generate(std::vector <Point> &vector, Rectangle box, int nX, int nY) {
    double dX = box.getWidth()/nX;
    double dY = box.getHeight()/nY;

    for(int i = 0; i<nY; i++){
        for(int j = 0; j<nX; j++){
            double x = box.xMin() + j*dX;
            double y = box.yMin() + i*dY;

            vector.push_back(Point(lX(x), lY(y)));
        }
    }
}



