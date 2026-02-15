#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e4 + 5;

bitset<N> vis;
vector<int> adj[N];

void initialize(int n) {
    for(int i = 0; i < n; ++i)
        adj[i].clear();
    vis.reset();
}

void dfs(int u) {
    if(vis[u]) return;
    vis[u] = 1;
    for(int v : adj[u]) dfs(v);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int tc;

    cin >> tc;

    while(tc--) {
        int n, m, q;

        cin >> n >> m >> q;

        initialize(n);

        while(m-- > 0) {
            int x, y;
            cin >> x >> y;
            adj[x - 1].push_back(y - 1);
        }

        while(q--) {
            int u;
            cin >> u;
            dfs(u - 1);
        }

        cout << vis.count() << '\n';
    }

    return 0;
}
