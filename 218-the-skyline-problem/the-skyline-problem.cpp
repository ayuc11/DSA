class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {

        vector<pair<int, int>> events;

        // Create start and end events
        for (auto& b : buildings) {

            int left = b[0];
            int right = b[1];
            int height = b[2];

            events.push_back({left, height});    // start
            events.push_back({right, -height});  // end
        }

        // Sort events by x
        sort(events.begin(), events.end());

        vector<vector<int>> ans;

        // Max heap
        multiset<int> heights;

        // Ground level
        heights.insert(0);

        int previousHeight = 0;

        int i = 0;

        while (i < events.size()) {

            int x = events[i].first;

            // Process ALL events having same x
            while (i < events.size() && events[i].first == x) {

                int h = events[i].second;

                if (h > 0) {
                    // Building starts
                    heights.insert(h);
                }
                else {
                    // Building ends
                    heights.erase(heights.find(-h));
                }

                i++;
            }

            // Current maximum height
            int currentHeight = *heights.rbegin();

            // Height changed → skyline point
            if (currentHeight != previousHeight) {

                ans.push_back({x, currentHeight});

                previousHeight = currentHeight;
            }
        }

        return ans;
    }
};