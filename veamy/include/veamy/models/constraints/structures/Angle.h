#ifndef THESIS_ANGLE_H
#define THESIS_ANGLE_H

#include <cmath>
#include <veamy/config/VeamyConfig.h>

struct Angle{
    double angle;

    Angle(double a){
        if(a>=0 && a<180) {
            angle = a;
        }else{
            angle = a - 180;
        }
    }

    bool operator<(const Angle& other) const{
        VeamyConfig* config = VeamyConfig::instance();

        if(std::abs(angle-other.angle)<config->getTolerance()){
            return false;
        }

        return angle<other.angle;
    };
};

#endif 
