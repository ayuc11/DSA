class Solution {
public:

    bool better(pair<long long, vector<int>>& a,
                pair<long long, vector<int>>& b) {

        if (a.first != b.first)
            return a.first > b.first;

        // Sort indices before comparing
        vector<int> x = a.second;
        vector<int> y = b.second;

        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        return x < y;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            return x[3] < y[3];
        });

        // Previous non-overlapping interval
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {

            int lo = 0;
            int hi = i;

            while (lo < hi) {

                int mid = lo + (hi - lo) / 2;

                if (a[mid][1] < a[i][0])
                    lo = mid + 1;
                else
                    hi = mid;
            }

            prev[i] = lo;
        }

        // dp[k][i]
        vector<vector<pair<long long, vector<int>>>> dp(
            5, vector<pair<long long, vector<int>>>(n + 1)
        );

        for (int k = 1; k <= 4; k++) {

            for (int i = 1; i <= n; i++) {

                // Don't take current interval
                auto skip = dp[k][i - 1];

                // Take current interval
                auto take = dp[k - 1][prev[i - 1]];

                take.first += a[i - 1][2];
                take.second.push_back((int)a[i - 1][3]);

                if (better(take, skip))
                    dp[k][i] = take;
                else
                    dp[k][i] = skip;
            }
        }

        vector<int> ans = dp[4][n].second;

        // Final answer must be sorted by original index
        sort(ans.begin(), ans.end());

        return ans;
    }
};