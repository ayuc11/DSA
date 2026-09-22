class Solution {
public:
    vector<vector<int>> ans;
    vector<int> current;

    void backtrack(vector<int>& nums, vector<bool>& used) {
        // Permutation complete
        if (current.size() == nums.size()) {
            ans.push_back(current);
            return;
        }

        // Try every unused number
        for (int i = 0; i < nums.size(); i++) {

            if (used[i])
                continue;

            // Choose
            used[i] = true;
            current.push_back(nums[i]);

            // Explore
            backtrack(nums, used);

            // Undo (Backtrack)
            current.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);

        backtrack(nums, used);

        return ans;
    }
};