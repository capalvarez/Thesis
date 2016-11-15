#ifndef THESIS_STRINGUTILS_H
#define THESIS_STRINGUTILS_H

#include <iostream>
#include <sstream>

namespace string_utils{
    template <typename T>
    extern std::string toString(T a);

    extern std::string getPath();
}

#endif 
