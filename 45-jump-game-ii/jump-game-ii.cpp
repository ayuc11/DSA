#include <vector>
#include <algorithm>

class Solution {
public:
    int jump(std::vector<int>& nums) {
        int n = nums.size();
        
        // If the array has 1 or fewer elements, no jumps are needed.
        if (n <= 1) {
            return 0;
        }
        
        int jumps = 0;
        int current_end = 0;
        int farthest = 0;
        
        // We only iterate up to n - 1 because we don't need to jump 
        // if we are already at the last element.
        for (int i = 0; i < n - 1; ++i) {
            // Constantly update the farthest index we can reach
            farthest = std::max(farthest, i + nums[i]);
            
            // When we reach the boundary of our current jump range
            if (i == current_end) {
                jumps++;                 // We must take a jump
                current_end = farthest;  // Update the boundary of the next jump
                
                // Optimization: If the new boundary reaches or exceeds 
                // the last index, we can stop early.
                if (current_end >= n - 1) {
                    break;
                }
            }
        }
        
        return jumps;
    }
};