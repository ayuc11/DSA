#include <vector>
#include <array>

using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        vector<vector<array<int, 2>>> memo(m, vector<array<int, 2>>(n, {-2, -2}));

        auto trace = [&](auto& self, int r, int c, int dir) -> pair<int, int> {
            if (r >= m || c >= n) return {-1, -1};
            if (grid[r][c] == 0) return {r, c};

            if (memo[r][c][dir] != -2) {
                if (memo[r][c][dir] == -1) return {-1, -1};
                return {memo[r][c][dir] >> 16, memo[r][c][dir] & 0xFFFF};
            }

            pair<int, int> res;
            if (dir == 0) {
                res = self(self, r + 1, c, 1);
            } else {
                res = self(self, r, c + 1, 0);
            }

            if (res.first == -1) {
                memo[r][c][dir] = -1;
            } else {
                memo[r][c][dir] = (res.first << 16) | res.second;
            }
            return res;
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][j] == 0) continue;

                auto [r1, c1] = trace(trace, i, j + 1, 0);
                if (r1 != -1) {
                    dp[r1][c1] = (dp[r1][c1] + dp[i][j]) % MOD;
                }

                auto [r2, c2] = trace(trace, i + 1, j, 1);
                if (r2 != -1) {
                    dp[r2][c2] = (dp[r2][c2] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};