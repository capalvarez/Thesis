#include <sstream>
#include <vector>

namespace utilities {
    template <typename T>
    std::string ToString(T val){
        std::stringstream stream;
        stream << val;
        return stream.str();
    }

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
}

