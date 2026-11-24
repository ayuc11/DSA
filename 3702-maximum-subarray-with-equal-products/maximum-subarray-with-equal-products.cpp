class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 2;
        long long prod = 1;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            while (std::gcd(prod, (long long)nums[right]) > 1) {
                prod /= nums[left];
                left++;
            }
            prod *= nums[right];
            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};