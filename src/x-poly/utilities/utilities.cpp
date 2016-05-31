#include <sstream>

namespace utilities {
    template <typename T>
    std::string ToString(T val){
        std::stringstream stream;
        stream << val;
        return stream.str();
    }

}

