#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5e2 + 5;

int parent[N], depth[N], cnt[N], cnt_edges[N];
long long cost[N];

void initialize(int n) {
    for(int i = 0; i < n; ++i) {
        parent[i] = i;
        depth[i] = 0;
        cnt[i] = 1;
        cnt_edges[i] = 0;
        cost[i] = 0;
    }
}

int find_set(int u) {
    return u == parent[u] ? u : parent[u] = find_set(parent[u]);
}

bool unite(int u, int v, int w) {
    u = find_set(u);
    v = find_set(v);

    if(u == v) return false;
    else if(depth[u] > depth[v]) swap(u, v);

    parent[u] = v;
    depth[v] += depth[u] == depth[v];
    cnt[v] += cnt[u];
    cnt_edges[v] += cnt_edges[u] + 1;
    cost[v] += cost[u] + w;

    return true;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int n, m;

    while(cin >> n >> m && n + m) {
        initialize(n);
        
        using E = tuple<int, int, int>;

        vector<E> edges;

        edges.reserve(m);

        for(int i = 0; i < m; ++i) {    
            int u, v, w;

            cin >> u >> v >> w;

            edges.emplace_back(w, u - 1, v - 1);
        }

        sort(edges.rbegin(), edges.rend());

        auto ans = make_pair(numeric_limits<double>::lowest(), 0);

        for(auto& e : edges) {
            int u, v, w;

            tie(w, u, v) = e;

            if(!unite(u, v, w)) {
                int x = find_set(u);
                cost[x] += w;
                ++cnt_edges[x];
            }

            int x = find_set(u);
            ans = max(ans, make_pair(1.0 * cost[x] / cnt_edges[x], cnt[x]));
        }

        cout << ans.second << '\n';
    }

    return 0;
}
