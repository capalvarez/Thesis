#ifndef THESIS_ANGLE_H
#define THESIS_ANGLE_H

#include <cmath>

struct Angle{
    double angle;

    Angle(double a){
        angle = a;
    }

    bool operator<(const Angle& other) const{
        if(std::abs(angle-other.angle)<0.001){
            return false;
        }

        return angle<other.angle;
    };
};

#endif 
