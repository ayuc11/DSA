class Solution {
public:
    string countAndSay(int n) {
        string s = "1";
        
        for (int i = 2; i <= n; ++i) {
            string next_s = "";
            int len = s.length();
            
            for (int j = 0; j < len; ) {
                int count = 0;
                char ch = s[j];
                
                // Count consecutive identical characters
                while (j < len && s[j] == ch) {
                    count++;
                    j++;
                }
                
                next_s += to_string(count);
                next_s += ch;
            }
            
            s = move(next_s);
        }
        
        return s;
    }
};