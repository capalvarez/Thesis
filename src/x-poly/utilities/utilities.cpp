#include <sstream>
#include <vector>

namespace utilities {
    template <typename T>
    std::string ToString(T val){
        std::stringstream stream;
        stream << val;
        return stream.str();
    }

    std::vector<int> TrivialIndexVector(int n){
        std::vector<int> index_vector;
        for(int i=0;i<n; i++){
            index_vector.push_back(i);
        }

        return index_vector;
    }

}

