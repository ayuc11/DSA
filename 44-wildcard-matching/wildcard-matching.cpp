class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0;

        int star = -1;       // Last '*' ka position in pattern
        int match = -1;      // '*' se kitne characters match kiye

        while (i < s.length()) {

            // Normal character ya '?'
            if (j < p.length() &&
                (p[j] == '?' || p[j] == s[i])) {
                i++;
                j++;
            }

            // '*'
            else if (j < p.length() && p[j] == '*') {
                star = j;
                match = i;
                j++;
            }

            // Mismatch, but pehle '*' mila tha
            else if (star != -1) {
                j = star + 1;
                match++;
                i = match;
            }

            // No '*' and mismatch
            else {
                return false;
            }
        }

        // Remaining pattern mein sirf '*' hone chahiye
        while (j < p.length() && p[j] == '*') {
            j++;
        }

        return j == p.length();
    }
};