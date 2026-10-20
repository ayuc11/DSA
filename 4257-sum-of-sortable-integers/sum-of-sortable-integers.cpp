#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            if (k == 1) {
                if (is_sorted(nums.begin(), nums.end())) {
                    ans += 1;
                }
                continue;
            }

            bool ok = true;
            int prev_max = -1;

            for (int start = 0; start < n; start += k) {
                int end = start + k - 1;
                int descents = 0;
                int drop_idx = -1;

                for (int i = start; i < end; i++) {
                    if (nums[i] > nums[i + 1]) {
                        descents++;
                        drop_idx = i;
                    }
                }
                // Check cycle wrap-around
                if (nums[end] > nums[start]) {
                    descents++;
                    if (drop_idx == -1) {
                        drop_idx = end;
                    }
                }

                if (descents > 1) {
                    ok = false;
                    break;
                }

                int block_min, block_max;
                if (descents == 0) {
                    block_min = nums[start];
                    block_max = nums[end];
                } else {
                    if (drop_idx == end) {
                        block_min = nums[start];
                        block_max = nums[end];
                    } else {
                        block_min = nums[drop_idx + 1];
                        block_max = nums[drop_idx];
                    }
                }

                if (block_min < prev_max) {
                    ok = false;
                    break;
                }
                prev_max = block_max;
            }

            if (ok) {
                ans += k;
            }
        }

        return (int)ans;
    }
};