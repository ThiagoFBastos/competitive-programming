#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using ii = pair<ll, int>;
using vii = vector<ii>;
using vi = vector<int>;
const int MAXN = 1e5;
vi G[MAXN];
vii D[MAXN], Drev[MAXN];
int n, m, low[MAXN], t[MAXN], p[MAXN], k = 0, r = 0;
bool j[MAXN], cm[MAXN];
void dfs(int v) {
	low[v] = t[v] = k++;
	for(int u : G[v]) {
		if(t[u] == -1) {
			p[u] = v;
			dfs(u);
			if(low[u] >= t[v]) j[v] = true;
			low[v] = min(low[v], low[u]);
		}
		else if(p[v] != u) low[v] = min(low[v], t[u]);
	}
	if(j[v] || v == 0 || v == n - 1) ++r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	priority_queue<ii, vii, greater<ii>> pq;
	queue<int> S;
	ll cost[MAXN];
	cin >> n >> m;
	for(int v = 0; v < n; ++v) {
		cost[v] = t[v] = -1;
		j[v] = cm[v] = false;
	}
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		D[u].push_back({w, v});
		Drev[v].push_back({w, u});
	}
	if(n == 1) cout << "1\n";
	else {
		pq.push({0, 0});
		while(!pq.empty()) {
			auto [c, v] = pq.top();
			pq.pop();
			if(cost[v] != -1) continue;
			cost[v] = c;
			for(auto [w, u] : D[v]) if(cost[u] == -1) pq.push({c + w, u});
		}
		S.push(n - 1);
		cm[n - 1] = true;
		while(!S.empty()) {
			int v = S.front();
			S.pop();
			for(auto [w, u] : Drev[v]) {
				if(cost[u] != -1 && cost[u] + w == cost[v]) {
					G[u].push_back(v);
					G[v].push_back(u);
					if(!cm[u]) {
						cm[u] = true;
						S.push(u);
					}
				}
			}
		}	
		dfs(0);
		cout << r << '\n' << "1 ";
		for(int v = 1; v < n - 1; ++v) if(j[v]) cout << v + 1 << ' ';
		cout << n << '\n';
	}
	return 0;
}