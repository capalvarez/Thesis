#include <unordered_map>
#include <vector>
#include <iostream>

int main(){
    std::unordered_map<int,std::vector<int>> map;
    int test[10] = {1,2,3,1,2,5,6,7,5,3};

    for (int i = 0; i < 10; ++i) {
        map[test[i]].push_back(test[i]);
    }

    std::cout << "hi!";



}