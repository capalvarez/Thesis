#include <functional>

namespace functions {
    std::function<double(double)> constant(){
        return [](int x) {return x;};
    }

    std::function<double(double)> uniform(int delta){
        return [delta](int x) { return delta*x;};
    }

    std::function<double(double)> random(){
        return [](int x){ return 1;};
    }
}
