#include <algorithm>

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
}


