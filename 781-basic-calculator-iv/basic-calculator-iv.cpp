class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string, int> eval;
        for (int i = 0; i < evalvars.size(); ++i) {
            eval[evalvars[i]] = evalints[i];
        }

        Parser parser(expression, eval);
        auto poly = parser.parse();
        return format(poly);
    }

private:
    using Poly = map<vector<string>, long long>;

    struct Parser {
        string s;
        int pos = 0;
        unordered_map<string, int> eval;

        Parser(const string& str, const unordered_map<string, int>& e) : s(str), eval(e) {}

        void skip() {
            while (pos < s.size() && s[pos] == ' ') ++pos;
        }

        Poly parse() {
            return parseExpr();
        }

        Poly parseExpr() {
            Poly res = parseTerm();
            while (true) {
                skip();
                if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
                    char op = s[pos++];
                    Poly rhs = parseTerm();
                    if (op == '+') res = add(res, rhs);
                    else res = sub(res, rhs);
                } else {
                    break;
                }
            }
            return res;
        }

        Poly parseTerm() {
            Poly res = parseFactor();
            while (true) {
                skip();
                if (pos < s.size() && s[pos] == '*') {
                    ++pos;
                    Poly rhs = parseFactor();
                    res = mul(res, rhs);
                } else {
                    break;
                }
            }
            return res;
        }

        Poly parseFactor() {
            skip();
            if (s[pos] == '(') {
                ++pos;
                Poly res = parseExpr();
                skip();
                if (pos < s.size() && s[pos] == ')') ++pos;
                return res;
            }

            if (isdigit(s[pos])) {
                long long num = 0;
                while (pos < s.size() && isdigit(s[pos])) {
                    num = num * 10 + (s[pos] - '0');
                    ++pos;
                }
                Poly p;
                p[{}] = num;
                return p;
            }

            string var;
            while (pos < s.size() && islower(s[pos])) {
                var += s[pos++];
            }

            Poly p;
            if (eval.count(var)) {
                p[{}] = eval[var];
            } else {
                p[{var}] = 1;
            }
            return p;
        }

        Poly add(const Poly& a, const Poly& b) {
            Poly res = a;
            for (auto& [k, v] : b) res[k] += v;
            return res;
        }

        Poly sub(const Poly& a, const Poly& b) {
            Poly res = a;
            for (auto& [k, v] : b) res[k] -= v;
            return res;
        }

        Poly mul(const Poly& a, const Poly& b) {
            Poly res;
            for (auto& [ka, va] : a) {
                for (auto& [kb, vb] : b) {
                    vector<string> key = ka;
                    key.insert(key.end(), kb.begin(), kb.end());
                    sort(key.begin(), key.end());
                    res[key] += va * vb;
                }
            }
            return res;
        }
    };

    vector<string> format(Poly& poly) {
        vector<pair<vector<string>, long long>> terms;
        for (auto& [k, v] : poly) {
            if (v != 0) terms.push_back({k, v});
        }

        sort(terms.begin(), terms.end(), [](const auto& a, const auto& b) {
            if (a.first.size() != b.first.size()) {
                return a.first.size() > b.first.size();
            }
            return a.first < b.first;
        });

        vector<string> ans;
        for (auto& [vars, coef] : terms) {
            string term = to_string(coef);
            for (auto& v : vars) {
                term += "*" + v;
            }
            ans.push_back(term);
        }
        return ans;
    }
};