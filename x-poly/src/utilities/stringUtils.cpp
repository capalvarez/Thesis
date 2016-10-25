#include <iostream>
#include <sstream>

namespace string_utils{
    template <typename T>
    std::string toString(T a){
        std::stringstream sstream;
        sstream << a;
        std::string s = sstream.str();

        return s;
    }

    template std::string toString<double>(double a);
}