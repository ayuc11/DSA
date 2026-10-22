class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int pos = 0;
        while (pos < n && nums[pos] != 0) {
            pos++;
        }

        bool normal = true;
        bool reversed = true;

        for (int i = 0; i < n; i++) {
            if (nums[(pos + i) % n] != i) normal = false;
            if (nums[(pos - i + n) % n] != i) reversed = false;
        }

        if (!normal && !reversed) return -1;

        int ans = INT_MAX;

        if (normal) {
            ans = min(ans, pos);
            if (pos != 0) {
                ans = min(ans, (n - pos) + 2);
            }
        }

        if (reversed) {
            ans = min(ans, 1 + (n - 1 - pos));
            ans = min(ans, ((pos + 1) % n) + 1);
        }

        return ans;
    }
};