#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Node {
        int prod;
        array<int, 5> pref;

        Node() {
            prod = 1;
            pref.fill(0);
        }
    };

    int n, k;
    int size;
    vector<Node> tree;

    Node mergeNode(const Node& A, const Node& B) {
        Node C;

        C.prod = (long long)A.prod * B.prod % k;

        // Prefixes completely inside A
        for (int x = 0; x < k; x++) {
            C.pref[x] = A.pref[x];
        }

        // Prefix = whole A + prefix of B
        for (int x = 0; x < k; x++) {
            if (B.pref[x]) {
                int rem = (long long)A.prod * x % k;
                C.pref[rem] += B.pref[x];
            }
        }

        return C;
    }

    void update(int pos, int value) {
        pos += size;

        tree[pos] = Node();

        int rem = value % k;

        tree[pos].prod = rem;
        tree[pos].pref[rem] = 1;

        pos >>= 1;

        while (pos) {
            tree[pos] = mergeNode(tree[pos << 1],
                                  tree[pos << 1 | 1]);
            pos >>= 1;
        }
    }

    Node query(int l, int r) {
        // Query [l, r)
        Node leftRes;
        Node rightRes;

        bool hasLeft = false;
        bool hasRight = false;

        l += size;
        r += size;

        while (l < r) {

            if (l & 1) {
                if (!hasLeft) {
                    leftRes = tree[l];
                    hasLeft = true;
                } else {
                    leftRes = mergeNode(leftRes, tree[l]);
                }
                l++;
            }

            if (r & 1) {
                --r;

                if (!hasRight) {
                    rightRes = tree[r];
                    hasRight = true;
                } else {
                    rightRes = mergeNode(tree[r], rightRes);
                }
            }

            l >>= 1;
            r >>= 1;
        }

        if (!hasLeft)
            return rightRes;

        if (!hasRight)
            return leftRes;

        return mergeNode(leftRes, rightRes);
    }

public:
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->k = k;
        n = nums.size();

        // Iterative segment tree size
        size = 1;

        while (size < n)
            size <<= 1;

        tree.assign(2 * size, Node());

        // Build leaves
        for (int i = 0; i < n; i++) {
            int rem = nums[i] % k;

            tree[size + i].prod = rem;
            tree[size + i].pref[rem] = 1;
        }

        // Build tree
        for (int i = size - 1; i >= 1; i--) {
            tree[i] = mergeNode(tree[i << 1],
                                tree[i << 1 | 1]);
        }

        vector<int> result;
        result.reserve(queries.size());

        for (auto& q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(index, value);

            // Query [start, n)
            Node ans = query(start, n);

            result.push_back(ans.pref[x]);
        }

        return result;
    }
};