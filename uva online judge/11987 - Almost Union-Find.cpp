#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e5 + 5;

unsigned parent[N], depth[N], size[N], who[N], current;
long long sum[N];

void add(int v, int w) {
    parent[v] = v;
    depth[v] = 0;
    size[v] = 1;
    sum[v] = w;
}

void initialize(unsigned n) {
    for(int i = 0; i < n; ++i) {
        who[i] = i;
        add(i, i + 1);
    }
}

unsigned find_set(unsigned v) {
    return v == parent[v] ? v : parent[v] = find_set(parent[v]);
}

void unite(unsigned u, unsigned v) {
    u = find_set(u);
    v = find_set(v);

    if(u == v) return;
    else if(depth[u] > depth[v]) swap(u, v);

    parent[u] = v;
    size[v] += size[u];
    sum[v] += sum[u];
    depth[v] += depth[u] == depth[v];
}

void remove(int u) {
    auto v = find_set(who[u]);
    --size[v];
    sum[v] -= u + 1;
    who[u] = current++;
    add(who[u], u + 1);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    unsigned n, m;

    while(cin >> n >> m) {

        initialize(n);

        current = n;

        for(unsigned i = 0; i < m; ++i) {
            unsigned t, p, q;

            cin >> t >> p;

            --p;

            if(t == 1) {
                cin >> q;

                --q;

                unite(who[p], who[q]);
            } else if(t == 2) {
                cin >> q;

                --q;

                if(find_set(who[p]) != find_set(who[q])) {
                    remove(p);
                    unite(who[p], who[q]);
                }
            } else {
                auto u = find_set(who[p]);

                cout << size[u] << ' ' << sum[u] << '\n';
            }
        }
    }

    return 0;
}
