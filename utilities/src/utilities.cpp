#include <algorithm>
#include <utilities/Pair.h>

namespace utilities {
    int random_integer(int min, int max){
        static std::random_device rd;
        static std::mt19937 rng (rd());
        std::uniform_int_distribution<int> uni(min,max);

        return uni(rng);
    }

    double truncate(double number, int precision){
        double p = std::pow(10,precision);

        return ((double)((int) (number*p)))/p;
    }

    std::string getPath(){
        #if defined(_WIN64) || defined(_WIN32)
                std::string path = std::getenv("USERPROFILE");
                return  path + "\\";
        #elif defined(__linux__)
                std::string psth = std::getenv("HOME");
                return path + "/";
        #endif
    }

    Pair<double> normalize(Pair<double> vector){
        double norm = std::sqrt(std::pow(vector.first,2) + std::pow(vector.second,2));

        return Pair<double>(vector.first/norm, vector.second/norm);
    }
}


