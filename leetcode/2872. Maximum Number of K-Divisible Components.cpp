class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> adj(n);
        vector<long long> sum(n);
        int components {};

        for(const auto& edge : edges) {
            assert(edge.size() == 2);

            const int u = edge[0];
            const int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        auto dfs = [&](auto& self, const int u, const int p) -> void {
            sum[u] = values[u];

            for(const int v : adj[u]) {
                if(v == p) continue;
                self(self, v, u);
                sum[u] += sum[v];
            }

            if(sum[u] % k == 0) {
                ++components;
                sum[u] = 0;
            }
        };

        dfs(dfs, 0, -1);

        return components;
    }
};