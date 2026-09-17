class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        // best[i] = minimum length of a valid subarray
        // completely inside arr[0 ... i]
        vector<int> best(n, INT_MAX);

        int left = 0;
        long long sum = 0;

        int ans = INT_MAX;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window while sum is too large
            while (sum > target) {
                sum -= arr[left++];
            }

            // We found a subarray [left ... right]
            if (sum == target) {
                int len = right - left + 1;

                // Combine with the best subarray
                // that ends before 'left'
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, len + best[left - 1]);
                }

                // This is the shortest valid subarray
                // ending at 'right'
                minLen = min(minLen, len);
            }

            // Carry forward the best subarray found so far
            best[right] = minLen;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};