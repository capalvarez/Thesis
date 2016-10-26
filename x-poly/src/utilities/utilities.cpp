#define _USE_MATH_DEFINES


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

    double degrees(double angle){
        return (angle > 0 ? angle : (2*M_PI + angle)) * 360 / (2*M_PI);
    }

    template <typename T>
    int indexOf(std::vector<T> vector, T element){
        int pos = std::find(vector.begin(), vector.end(), element) - vector.begin();

        return pos < (int) vector.size()? pos : -1;
    }
    template int indexOf<Point>(std::vector<Point> vector, Point p);
    template int indexOf<int>(std::vector<int> vector, int p);

    int random_integer(int min, int max){
        static std::random_device rd;
        static std::mt19937 rng (rd());
        std::uniform_int_distribution<int> uni(min,max);

        return uni(rng);
    }


}

