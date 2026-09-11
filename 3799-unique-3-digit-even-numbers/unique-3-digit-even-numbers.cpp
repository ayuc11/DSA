class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int freq[10] = {};

        // Count available copies of each digit
        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // Try every 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Must be even
            if (num % 2 != 0)
                continue;

            int x = num;
            int need[10] = {};

            // Extract its three digits
            while (x > 0) {
                need[x % 10]++;
                x /= 10;
            }

            // Check whether we have enough copies
            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};