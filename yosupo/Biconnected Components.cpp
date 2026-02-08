#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int N = 5e5 + 10;

int n, m, low[N], in[N], last[N], times, bid;
vector<ii> adj[N];
vector<int> st, block[N];

void dfs(int u, int p, int e) {
	low[u] = in[u] = times++;
	for(auto [v, cur_e] : adj[u]) {
		if(in[v] < 0) {
			dfs(v, u, cur_e);
			low[u] = min(low[u], low[v]);
			if(low[v] >= in[u]) {
				while(!st.empty()) {
					int v = st.back();
					if(low[v] < in[u]) break;
					st.pop_back();
					if(last[v] != bid) block[bid].pb(v);
					last[v] = bid;
					for(auto [u, e] : adj[v]) {
						if(in[u] >= in[v] || last[u] == bid) continue;
						last[u] = bid; 
						block[bid].pb(u);
					}
				}
				++bid;
			}
		} else if(ii(v, cur_e) != ii(p, e))
			low[u] = min(low[u], in[v]);
	}
	st.pb(u);
}

void solve() {
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].pb({v, i});
		adj[v].pb({u, i});
	}
	memset(in, -1, sizeof(int) * n);	
	memset(last, -1, sizeof(int) * n);
	for(int i = 0; i < n; ++i) {
		if(in[i] != -1) continue;
		int check = times;
		st.clear();
		dfs(i, -1, -1);
		if(times - check == 1) block[bid++].pb(i);
	}	
	cout << bid << '\n';
	for(int i = 0; i < bid; ++i) {
		cout << block[i].size() << ' ';
		for(int v : block[i]) cout << v << ' ';
		cout << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}