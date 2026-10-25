#include <vector>

class Solution {
private:
    void dfs(int r, int c, std::vector<std::vector<int>>& grid, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != 0) {
            return;
        }
        
        grid[r][c] = 1;
        
        dfs(r + 1, c, grid, m, n);
        dfs(r - 1, c, grid, m, n);
        dfs(r, c + 1, grid, m, n);
        dfs(r, c - 1, grid, m, n);
    }

public:
    int closedIsland(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) dfs(i, 0, grid, m, n);
            if (grid[i][n - 1] == 0) dfs(i, n - 1, grid, m, n);
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 0) dfs(0, j, grid, m, n);
            if (grid[m - 1][j] == 0) dfs(m - 1, j, grid, m, n);
        }
        
        int closedIslands = 0;
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (grid[i][j] == 0) {
                    dfs(i, j, grid, m, n);
                    closedIslands++;
                }
            }
        }
        
        return closedIslands;
    }
};