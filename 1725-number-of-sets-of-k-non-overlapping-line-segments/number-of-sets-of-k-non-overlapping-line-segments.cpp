class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        // dp[i][j] = number of ways to draw exactly j segments
        // using the first i points (0 ... i-1)
        vector<vector<long long>> dp(n + 1,
                                     vector<long long>(k + 1, 0));

        // With 0 segments, there is exactly 1 way
        // (choose nothing).
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= k; j++) {

            long long prefix = 0;

            for (int i = 1; i <= n; i++) {

                // Don't use point i-1 as the endpoint
                dp[i][j] = dp[i - 1][j];

                // Start the last segment somewhere before i-1
                dp[i][j] = (dp[i][j] + prefix) % MOD;

                // Add dp[i][j-1] for future positions
                prefix = (prefix + dp[i][j - 1]) % MOD;
            }
        }

        return dp[n][k];
    }
};