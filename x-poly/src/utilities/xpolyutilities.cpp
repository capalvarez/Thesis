#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <x-poly/models/basic/Point.h>
#include <utilities/Pair.h>

namespace xpoly_utilities {
    void TrivialIndexVector(std::vector<int>& index_vector, int n){
        for(int i=0;i<n; i++){
            index_vector.push_back(i);
        }
    }

    double radian(double angle){
        return angle*M_PI/180;
    }

    double degrees(double angle){
        return (angle > 0 ? angle : (2*M_PI + angle)) * 360 / (2*M_PI);
    }

    double crossProduct(Point a, Point b){
        return a.getX()*b.getY() - a.getY()*b.getX();
    }

    double norm(Point p){
        return sqrt(pow(p.getX(),2) + pow(p.getY(),2));
    }

    double orientation(Point p, Point q, Point r){
        return xpoly_utilities::crossProduct((q-p),(r-p));
    }
}

