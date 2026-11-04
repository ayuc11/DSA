#pragma GCC optimize("O3,unroll-loops")

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> cost(n, 0);
        
        multiset<int> left, right;
        long long sum_left = 0, sum_right = 0;
        int target_left = (x + 1) / 2;

        auto balance = [&]() {
            while ((int)left.size() > target_left) {
                auto it = prev(left.end());
                int val = *it;
                sum_left -= val;
                left.erase(it);
                right.insert(val);
                sum_right += val;
            }
            while ((int)left.size() < target_left && !right.empty()) {
                auto it = right.begin();
                int val = *it;
                sum_right -= val;
                right.erase(it);
                left.insert(val);
                sum_left += val;
            }
        };

        auto add_val = [&](int val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sum_left += val;
            } else {
                right.insert(val);
                sum_right += val;
            }
            balance();
        };

        auto remove_val = [&](int val) {
            auto it = left.find(val);
            if (it != left.end()) {
                sum_left -= val;
                left.erase(it);
            } else {
                it = right.find(val);
                sum_right -= val;
                right.erase(it);
            }
            balance();
        };

        for (int i = 0; i < n; ++i) {
            add_val(nums[i]);
            if (i >= x) {
                remove_val(nums[i - x]);
            }
            if (i >= x - 1) {
                long long median = *left.rbegin();
                cost[i] = (sum_right - (long long)right.size() * median) + 
                          ((long long)left.size() * median - sum_left);
            }
        }

        const long long INF = 1e18;
        vector<long long> prev_dp(n + 1, 0);

        for (int j = 1; j <= k; ++j) {
            vector<long long> curr_dp(n + 1, INF);
            for (int i = j * x; i <= n; ++i) {
                curr_dp[i] = curr_dp[i - 1];
                if (prev_dp[i - x] != INF) {
                    curr_dp[i] = min(curr_dp[i], prev_dp[i - x] + cost[i - 1]);
                }
            }
            prev_dp = move(curr_dp);
        }

        return prev_dp[n];
    }
};