#define _USE_MATH_DEFINES

#include <sstream>
#include <vector>
#include <math.h>
#include <x-poly/models/basic/Point.h>
#include <algorithm>


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

    template <typename T>
    int indexOf(std::vector<T> vector, T element){
        int pos = std::find(vector.begin(), vector.end(), element) - vector.begin();

        return pos < (int) vector.size()? pos : -1;
    }
    template int indexOf<Point>(std::vector<Point> vector, Point p);

    int random_integer(int min, int max){
        std::random_device rd;
        std::mt19937 rng (rd());
        std::uniform_int_distribution<int> uni(min,max);

        return uni(rng);
    }

}

