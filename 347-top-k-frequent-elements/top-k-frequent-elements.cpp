class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            ++freq[num];
        }

        int n = nums.size();
        vector<vector<int>> buckets(n + 1);
        for (auto& [num, cnt] : freq) {
            buckets[cnt].push_back(num);
        }

        vector<int> ans;
        for (int i = n; i >= 1 && ans.size() < k; --i) {
            for (int num : buckets[i]) {
                ans.push_back(num);
                if (ans.size() == k) break;
            }
        }

        return ans;
    }
};