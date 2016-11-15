#include <iostream>
#include <sstream>
#include <cstdlib>

namespace string_utils{
    template <typename T>
    std::string toString(T a){
        std::stringstream sstream;
        sstream << a;
        std::string s = sstream.str();

        return s;
    }

    template std::string toString<double>(double a);

    std::string getPath(){
        #if defined(_WIN64) || defined(_WIN32)
        return std::getenv("USERPROFILE");
        #elif defined(__linux__)
        return getenv("HOME");
        #endif
    }
}