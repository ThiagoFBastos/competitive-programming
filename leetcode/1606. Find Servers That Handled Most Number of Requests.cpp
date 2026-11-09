class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        using pq_type = pair<int, int>;
        vector<int> cnt(k, 0);
        set<int> serversID;
        priority_queue<pq_type, vector<pq_type>, greater<pq_type>> serversDeadline;
        int curID = 0;
        const int n = static_cast<int>(arrival.size());

        for(int i = 0; i < k; ++i)
            serversID.insert(i);

        for(int i = 0; i < n; ++i) {
            while(!serversDeadline.empty() && serversDeadline.top().first <= arrival[i]) {
                const auto [_, id] = serversDeadline.top();
                serversDeadline.pop();
                serversID.insert(id);
            }

            if(serversID.empty()) {
                curID = (curID + 1) % k;
                continue;
            }

            auto it = serversID.lower_bound(curID);

            if(it == serversID.end())
                it = serversID.begin();

            int id = *it;

            ++cnt[id];

            serversID.erase(it);

            serversDeadline.emplace(arrival[i] + load[i], id);

            curID = (curID + 1) % k;
        }

        const int max_cnt = ranges::fold_left(cnt, 0, ranges::max);

        auto ids = views::iota(0, k) | views::filter([&cnt, max_cnt](int id) {
            return cnt[id] == max_cnt;
        }) | ranges::to<vector<int>>();

        return ids;
    }
};