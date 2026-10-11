class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        constexpr int N = 15;
        vector<vector<int>> adj(n);
        int dp[N][N][N], sz[N];
        vector<int> answer(n - 1, 0);

        for(const auto& edge : edges) {
            assert(edge.size() == 2);
            const int u = edge[0] - 1, v = edge[1] - 1;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        auto merge = [&](int u, int v) {
            int tmp[N][N] = {{0}};

            for(int i = 0; i < sz[u]; ++i)
                for(int j = 0; j < sz[u]; ++j)
                    for(int k = 0; k < sz[v]; ++k)
                        for(int l = 0; l < sz[v]; ++l) {
                            int diameter = max({i, k, j + l + 1});
                            int depth = max(j, l + 1);
                            tmp[diameter][depth] += dp[u][i][j] * dp[v][k][l];
                        }

            sz[u] += sz[v];
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dp[u][i][j] += tmp[i][j];
        };

        auto dfs = [&](auto& self, const int u, const int p) -> void {
            dp[u][0][0] = 1;
            sz[u] = 1;

            for(const int v : adj[u]) {
                if(v == p) continue;
                self(self, v, u);
                merge(u, v);
            }
        };

        dfs(dfs, 0, -1);

        for(int u = 0; u < n; ++u)
            for(int i = 1; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    answer[i - 1] += dp[u][i][j];

        return answer;
    }
};