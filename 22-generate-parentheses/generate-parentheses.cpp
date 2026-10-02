class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        backtrack("", 0, 0, n, ans);
        return ans;
    }

    void backtrack(string s, int open, int close, int n,
                   vector<string>& ans) {


        if (open == n && close == n) {
            ans.push_back(s);
            return;
        }


        if (open < n) {
            backtrack(s + "(", open + 1, close, n, ans);
        }

        if (close < open) {
            backtrack(s + ")", open, close + 1, n, ans);
        }
    }
};