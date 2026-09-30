class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string curr;

        for (int i = 0; i <= path.size(); i++) {
            if (i == path.size() || path[i] == '/') {
                
                if (curr == "..") {
                    if (!st.empty())
                        st.pop_back();
                }
                else if (!curr.empty() && curr != ".") {
                    st.push_back(curr);
                }

                curr.clear();
            }
            else {
                curr += path[i];
            }
        }

        string ans;

        for (string dir : st) {
            ans += "/" + dir;
        }

        return ans.empty() ? "/" : ans;
    }
};