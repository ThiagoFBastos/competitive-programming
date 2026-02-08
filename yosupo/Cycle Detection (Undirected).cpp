#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5e5 + 5;

using edge = pair<int, int>;

vector<edge> adj[N], path;
int in[N], tms;
int n, m;

bool dfs(int u, int eup, vector<edge>& edges) {
	in[u] = tms++;
	
	for(auto [v, e] : adj[u]) {
		if(in[v] == -1) {
			path.emplace_back(u, e);
			if(dfs(v, e, edges))
				return true;
			path.pop_back();
		} else if(e != eup && in[u] >= in[v]) {
			path.emplace_back(u, e);

			while(true) {
				auto [x, y] = path.back();
				path.pop_back();
				edges.emplace_back(x, y);
				if(x == v) break;
			}

			reverse(edges.begin(), edges.end());

			return true;
		}
	}

	return false;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;

	memset(in, -1, sizeof(int) * n);

	for(int i = 0; i < m; ++i) {
		int u, v;

		cin >> u >> v;

		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
	}

	for(int u = 0; u < n; ++u) {
		if(in[u] != -1)
			continue;

		vector<edge> cycle;

		if(!dfs(u, -1, cycle))
			continue;

		cout << cycle.size() << '\n';

		for(auto [v, _] : cycle) cout << v << ' ';
		cout << '\n';
		for(auto [_, e] : cycle) cout << e << ' ';
		cout << '\n';

		return 0;
	}

	cout << "-1\n";

	return 0;
}
