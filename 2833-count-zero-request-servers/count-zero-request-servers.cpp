#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<int> ans(m);

        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> sorted_queries(m);
        for (int i = 0; i < m; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        sort(sorted_queries.begin(), sorted_queries.end());

        unordered_map<int, int> count;
        int left = 0, right = 0;
        int active_servers = 0;
        int total_logs = logs.size();

        for (const auto& [q_time, orig_idx] : sorted_queries) {
            int window_start = q_time - x;
            int window_end = q_time;

            while (right < total_logs && logs[right][1] <= window_end) {
                int server = logs[right][0];
                if (count[server] == 0) {
                    active_servers++;
                }
                count[server]++;
                right++;
            }

            while (left < total_logs && logs[left][1] < window_start) {
                int server = logs[left][0];
                count[server]--;
                if (count[server] == 0) {
                    active_servers--;
                }
                left++;
            }

            ans[orig_idx] = n - active_servers;
        }

        return ans;
    }
};