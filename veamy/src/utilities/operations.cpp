#include <veamy/utilities/operations.h>

namespace operations{
    double power(double base, double exp){
        return base!=0? pow(base,exp) : (exp!=0? 0 : 1);
    }
}

