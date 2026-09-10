class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (root == NULL)
            return {0, 0};

        // Left subtree
        auto left = dfs(root->left);

        // Right subtree
        auto right = dfs(root->right);

        // Current subtree ka sum and node count
        int sum = left.first + right.first + root->val;
        int count = left.second + right.second + 1;

        // Floor average
        int avg = sum / count;

        if (avg == root->val)
            ans++;

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};