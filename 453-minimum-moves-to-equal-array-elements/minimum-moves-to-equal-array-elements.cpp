#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int min_val = *std::min_element(nums.begin(), nums.end());
        long long total_moves = 0;
        
        for (int x : nums) {
            total_moves += (x - min_val);
        }
        
        return static_cast<int>(total_moves);
    }
};