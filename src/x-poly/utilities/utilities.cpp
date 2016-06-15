#include <sstream>
#include <vector>
#include <math.h>

namespace utilities {
    void TrivialIndexVector(std::vector<int> index_vector, int n){
        for(int i=0;i<n; i++){
            index_vector.push_back(i);
        }
    }

    template<class T>
    class DeleteVector{
    public:
        bool operator()(T x) const {
            delete x;
            return true;
        }
    };

    double radian(double angle){
        return angle*M_PI/180;
    }
}

