class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        int min_price = INT_MAX;

        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }

        vector<int> div_count(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            if (freq[f] == 0) continue;
            for (int mult = f; mult <= n; mult += f) {
                div_count[f] += freq[mult];
            }
        }

        vector<pair<int, int>> sorted_items;
        sorted_items.reserve(n);
        for (const auto& item : items) {
            int f = item[0];
            int p = item[1];
            int gain = div_count[f] - 1;
            if (gain > 0) {
                sorted_items.push_back({p, gain});
            }
        }

        sort(sorted_items.begin(), sorted_items.end());

        long long max_items = budget / min_price;
        long long current_items = 0;
        long long rem_budget = budget;

        for (const auto& [price, gain] : sorted_items) {
            if (rem_budget < price) break;

            long long can_buy = min((long long)gain, rem_budget / price);
            current_items += can_buy * 2;
            rem_budget -= can_buy * price;

            max_items = max(max_items, current_items + rem_budget / min_price);
        }

        return (int)max_items;
    }
};