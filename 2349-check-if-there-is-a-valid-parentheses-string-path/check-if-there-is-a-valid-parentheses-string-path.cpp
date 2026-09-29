class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        if ((m + n - 1) % 2 == 1)
            return false;

        vector<vector<bool>> dp(n, vector<bool>(m + n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int val = (grid[i][j] == '(') ? 1 : -1;

                if (i == 0 && j == 0) {
                    if (val == 1)
                        dp[j][1] = true;
                    continue;
                }

                vector<bool> cur(m + n, false);

                if (i > 0) {
                    for (int balance = 0; balance < m + n; balance++) {
                        if (dp[j][balance]) {
                            int newBalance = balance + val;
                            if (newBalance >= 0)
                                cur[newBalance] = true;
                        }
                    }
                }

                if (j > 0) {
                    for (int balance = 0; balance < m + n; balance++) {
                        if (dp[j - 1][balance]) {
                            int newBalance = balance + val;
                            if (newBalance >= 0)
                                cur[newBalance] = true;
                        }
                    }
                }

                dp[j] = cur;
            }
        }

        return dp[n - 1][0];
    }
};