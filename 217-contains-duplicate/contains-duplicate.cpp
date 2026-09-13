class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> seen;

        for (int num : nums) {

            // Already seen?
            if (seen.count(num)) {
                return true;
            }

            // First time seeing it
            seen.insert(num);
        }

        return false;
    }
};