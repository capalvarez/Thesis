#include <functional>
#include <random>
#include <iostream>
#include <utilities/utilities.h>

namespace functions {
    /*std::function<double(double)> constant(){
        return static_cast<std::function<double(double)> >();
    }

    std::function<double(double)> uniform(double delta){
        return ;
    }

    std::function<double(double)> random_double(double min, double max){
        srand(time(NULL));
        return [min, max](double x) {
            double f = (double)rand() / RAND_MAX;
            return min + f * (max - min);
        };
    }

    std::function<double(double)> random_integer(double min, double max){
        srand(time(NULL));
        return [min, max](double x) {
            return rand()%((int)max-(int)min + 1) + min;
        };
    }

    std::function<double(double)> sine(double amplitude, double frecuency, double phase){
        return [amplitude,frecuency,phase](double x){
            return amplitude*std::sin(frecuency*utilities::radian(x) + utilities::radian(phase));
        };
    }

    std::function<double(double)> cosine(double amplitude, double frecuency, double phase){
        return [amplitude, frecuency, phase](double x){
            return amplitude * std::cos(frecuency*utilities::radian(x) + utilities::radian(phase));
        };
    }*/
}

