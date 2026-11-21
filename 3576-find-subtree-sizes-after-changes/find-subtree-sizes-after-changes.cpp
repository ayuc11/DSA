class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> new_parent = parent;
        vector<int> last_seen(26, -1);

        auto dfs_reparent = [&](auto& self, int u) -> void {
            int char_idx = s[u] - 'a';
            int prev_ancestor = last_seen[char_idx];

            if (prev_ancestor != -1) {
                new_parent[u] = prev_ancestor;
            }

            last_seen[char_idx] = u;
            for (int v : adj[u]) {
                self(self, v);
            }
            last_seen[char_idx] = prev_ancestor;
        };

        dfs_reparent(dfs_reparent, 0);

        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            new_adj[new_parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        auto dfs_size = [&](auto& self, int u) -> int {
            for (int v : new_adj[u]) {
                ans[u] += self(self, v);
            }
            return ans[u];
        };

        dfs_size(dfs_size, 0);
        return ans;
    }
};