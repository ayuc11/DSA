class Solution {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;

public:
    void recoverTree(TreeNode* root) {
        inorder(root);
        if (first && second) {
            swap(first->val, second->val);
        }
    }
    
private:
    void inorder(TreeNode* root) {
        if (!root) return;
        
        inorder(root->left);
        
        if (prev && prev->val > root->val) {
            if (!first) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        
        inorder(root->right);
    }
};
