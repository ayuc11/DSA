class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> first_gain(n, 1);
        int min_price = 1e9;

        for (int i = 0; i < n; ++i) {
            min_price = min(min_price, items[i][1]);
            for (int j = 0; j < n; ++j) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    first_gain[i]++;
                }
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; ++i) {
            int price = items[i][1];
            int gain = first_gain[i];
            for (int b = budget; b >= price; --b) {
                dp[b] = max(dp[b], dp[b - price] + gain);
            }
        }

        for (int b = min_price; b <= budget; ++b) {
            dp[b] = max(dp[b], dp[b - min_price] + 1);
        }

        return dp[budget];
    }
};