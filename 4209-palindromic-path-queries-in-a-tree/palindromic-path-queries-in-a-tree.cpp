class Solution {
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth, bit;
    string s;
    int timer, LOG;

    void add(int i, int mask) {
        while (i < (int)bit.size()) {
            bit[i] ^= mask;
            i += i & -i;
        }
    }

    void rangeXor(int l, int r, int mask) {
        add(l, mask);
        add(r + 1, mask);
    }

    int getMask(int i) {
        int mask = 0;
        while (i > 0) {
            mask ^= bit[i];
            i -= i & -i;
        }
        return mask;
    }

    void dfs(int root) {
        int n = adj.size();
        vector<int> parent(n, -1);
        vector<pair<int, int>> st;
        st.push_back({root, 0});
        parent[root] = root;

        while (!st.empty()) {
            int u = st.back().first;
            int &state = st.back().second;

            if (state == 0) {
                tin[u] = ++timer;
                up[u][0] = parent[u];

                for (int j = 1; j < LOG; j++)
                    up[u][j] = up[up[u][j - 1]][j - 1];
            }

            if (state < (int)adj[u].size()) {
                int v = adj[u][state++];
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back({v, 0});
            } else {
                tout[u] = timer;
                st.pop_back();
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int d = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++)
            if (d & (1 << j))
                u = up[u][j];

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        this->s = s;
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        up.assign(n, vector<int>(LOG, 0));
        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        bit.assign(n + 2, 0);
        timer = 0;

        dfs(0);

        for (int u = 0; u < n; u++)
            rangeXor(tin[u], tout[u], 1 << (this->s[u] - 'a'));

        vector<bool> ans;

        for (string &q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta = (1 << (this->s[u] - 'a')) ^ (1 << (c - 'a'));
                rangeXor(tin[u], tout[u], delta);
                this->s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);
                int mask = getMask(tin[u]) ^ getMask(tin[v])
                         ^ (1 << (this->s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};