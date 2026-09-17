class Solution {
public:
    string minWindow(string s, string t) {
        if (s.length() < t.length())
            return "";

        vector<int> freq(128, 0);

        // Frequency of characters required from t
        for (char c : t) {
            freq[c]++;
        }

        int left = 0;
        int required = t.length();

        int minLen = INT_MAX;
        int start = 0;

        for (int right = 0; right < s.length(); right++) {

            // If this character is still needed
            if (freq[s[right]] > 0) {
                required--;
            }

            freq[s[right]]--;

            // Current window contains all characters of t
            while (required == 0) {

                // Update minimum window
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    start = left;
                }

                // Remove left character
                freq[s[left]]++;

                if (freq[s[left]] > 0) {
                    required++;
                }

                left++;
            }
        }

        if (minLen == INT_MAX)
            return "";

        return s.substr(start, minLen);
    }
};