#include <x-poly/models/polygon/Polygon.h>
#include <set>
#include <fracture/geometry/BreakableMesh.h>

namespace fracture_utilities{
    void allPairs(std::vector<Pair<int>>& pairs, std::vector<int> numbers) {
        int N = numbers.size();
        std::string bitmask(2, 1);
        bitmask.resize(N, 0);
        do {
            int f = -1;
            int s = -1;

            for (int i = 0; i < N; ++i){
                if (bitmask[i]){
                    if(f==-1){
                        f = i;
                    }else{
                        s = i;
                    }
                }
            }
            pairs.push_back(Pair<int>(numbers[f],numbers[s]));

        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
}