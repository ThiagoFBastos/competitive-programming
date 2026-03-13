#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

template<bool roll = false>
struct uf {
	vector<int> par, rank, sz;
	vector<tuple<int, int, int>> stackUPD;

	uf() {}

	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		if constexpr(roll)
			return v == par[v] ? v : par[v] = findSet(par[v]);
		else
			return v == par[v] ? v : findSet(par[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);

		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		
		if constexpr(roll)
			stackUPD.emplace_back(a, b, rank[b]);

		par[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];

		return true;
	}

	bool rollback() {
		if constexpr(roll) {
			if(stackUPD.empty()) return false;
			int u, v, r;
			tie(u, v, r) = stackUPD.back();
			stackUPD.pop_back();
			sz[v] -= sz[u];
			par[u] = u;
			rank[v] = r;
			return true;
		} else
			return false;
	}
};

void solve() {
	int n;
  
	cin >> n;

	vector<pair<ii, int>> p(n);
	uf dsu(n);
	vector<tuple<int, int, int>> e;

	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {{x, y}, i};
	}

	sort(all(p));

	for(int i = 1; i < n; ++i) e.pb({p[i].fi.fi-p[i-1].fi.fi, p[i-1].sc, p[i].sc});	

	for(auto& [x, _] : p) swap(x.fi, x.sc);

	sort(all(p));

	for(int i = 1; i < n; ++i) e.pb({p[i].fi.fi-p[i-1].fi.fi, p[i-1].sc, p[i].sc});

	sort(all(e));

	i64 cost = 0;

	for(auto [w, u, v] : e) if(dsu.join(u, v)) cost += w;
	
	cout << cost << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

