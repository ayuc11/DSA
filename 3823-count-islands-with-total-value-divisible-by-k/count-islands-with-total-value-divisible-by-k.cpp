#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int islandCount = 0;

        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    long long totalSum = 0;
                    queue<pair<int, int>> q;

                    q.push({i, j});
                    totalSum += grid[i][j];
                    grid[i][j] = 0;

                    while (!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();

                        for (auto& dir : dirs) {
                            int nr = r + dir[0];
                            int nc = c + dir[1];

                            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                                totalSum += grid[nr][nc];
                                grid[nr][nc] = 0;
                                q.push({nr, nc});
                            }
                        }
                    }

                    if (totalSum % k == 0) {
                        islandCount++;
                    }
                }
            }
        }

        return islandCount;
    }
};