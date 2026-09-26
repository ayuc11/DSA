class Solution {
public:
    string customSortString(string order, string s) {
        int freq[26] = {0};

        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string ans = "";

        for (char ch : order) {
            while (freq[ch - 'a'] > 0) {
                ans += ch;
                freq[ch - 'a']--;
            }
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {
            while (freq[ch - 'a'] > 0) {
                ans += ch;
                freq[ch - 'a']--;
            }
        }

        return ans;
    }
};