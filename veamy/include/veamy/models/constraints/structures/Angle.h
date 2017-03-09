#ifndef THESIS_ANGLE_H
#define THESIS_ANGLE_H

#include <cmath>

struct Angle{
    double angle;

    Angle(double a){
        if(a>=0 && a<=90) {
            angle = a;
        }else{
            if(a>90 && a<=180) {
                angle = 180 - a;
            } else{
                if(180<a && a<=270){
                    angle = a - 180;
                } else{
                    angle = 360 - a;
                }
            }
        }
    }

    bool operator<(const Angle& other) const{
        if(std::abs(angle-other.angle)<0.001){
            return false;
        }

        return angle<other.angle;
    };
};

#endif 
