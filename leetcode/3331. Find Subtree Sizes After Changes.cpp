class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        const int n = static_cast<int>(parent.size());
        vector<int> nodes[26], sz(n, 0);
        vector<vector<int>> adj(n);

        for(int i = 1; i < n; ++i)
            adj[parent[i]].push_back(i);

        auto dfs = [&](auto& self, int u) -> void {
            const int ch = s[u] - 'a';

            parent[u] = nodes[ch].empty() ? parent[u] : nodes[ch].back();
            nodes[ch].push_back(u);

            for(const int v : adj[u])
                self(self, v);

            nodes[ch].pop_back();
        };

        dfs(dfs, 0);

        for(auto& lst : adj)
            lst.clear();

         for(int i = 1; i < n; ++i)
            adj[parent[i]].push_back(i);

        auto dfs_size = [&](auto& self, int u) -> void {
            sz[u] = 1;
            for(int v : adj[u]) {
                self(self, v);
                sz[u] += sz[v];
            }
        };

        dfs_size(dfs_size, 0);

        return sz;
    }
};