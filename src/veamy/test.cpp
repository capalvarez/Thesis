#include <iostream>
#include <Eigen/Dense>

int main(){
    Eigen::Matrix2f a;
    a(0,0) = 1;
    a(1,1) = 1;
    a(0,1) = 0;
    a(1,0) = 0;

    std::cout << a << std::endl;
}

