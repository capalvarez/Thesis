#define _USE_MATH_DEFINES

#include <sstream>
#include <vector>
#include <math.h>


namespace utilities {
    void TrivialIndexVector(std::vector<int>& index_vector, int n){
        for(int i=0;i<n; i++){
            index_vector.push_back(i);
        }
    }

    double radian(double angle){
        return angle*M_PI/180;
    }
    template <typename T>
    std::string toString(T a){
        std::stringstream sstream;
        sstream << a;
        std::string s = sstream.str();

        return s;
    }
    template std::string toString<int>(int a);
    template std::string toString<double>(double a);
}

