class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> in, out;
        vector<int> tour;
        vector<vector<int>> answer;

        for(const auto& interval : pairs) {
            assert(interval.size() == 2);
            const int u = interval[0], v = interval[1];
            ++in[v];
            ++out[u];
            adj[u].push_back(v);
        }

        auto dfs = [&](auto& self, const int u) -> void {
            auto& neighbours = adj[u];

            while(!neighbours.empty()) {
                const int v = neighbours.back();
                neighbours.pop_back();
                self(self, v);
            }

            tour.push_back(u);
        };

        auto it = find_if(out.begin(), out.end(), [&in](const decltype(out)::value_type& p) {
            const auto [u, deg] = p;
            return deg - in[u] == 1;
        });

        if(it != out.end())
            dfs(dfs, it->first);
        else
            dfs(dfs, out.begin()->first);
            
        reverse(tour.begin(), tour.end());
        for(size_t i = 1; i < tour.size(); ++i)
            answer.push_back({tour[i - 1], tour[i]});

        return answer;
    }
};