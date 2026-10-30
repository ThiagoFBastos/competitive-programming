class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        using pq_type = tuple<int, int, int>;

        struct cmp {
            bool operator()(const pq_type& lhs, const pq_type& rhs) const {
                return get<0>(lhs) > get<0>(rhs);
            }
        };

        vector<vector<pair<int, int>>> adj(n);
        vector<vector<int>> cost(n, vector<int>(k + 1, -1));
        priority_queue<pq_type, vector<pq_type>, cmp> pq;

        for(const auto& edge : edges) {
            assert(edge.size() == 3);
            const int u = edge[0], v = edge[1], w = edge[2];
            adj[u].emplace_back(v, w);
        }

        pq.emplace(0, 0, 1);

        while(!pq.empty()) {
            const auto [cst, u, seq] = pq.top();

            pq.pop();

            if(cost[u][seq] != -1)
                continue;
            else if(u == n - 1)
                return cst;

            cost[u][seq] = cst;

            for(const auto& [v, w] : adj[u]) {
                const int repeated = labels[u] == labels[v] ? seq + 1 : 1;

                if(repeated > k || cost[v][repeated] != -1)
                    continue;

                pq.emplace(cst + w, v, repeated);
            }
        }

        return -1;
    }
};