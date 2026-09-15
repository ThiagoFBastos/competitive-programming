#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3,sse4,avx")

#include <bits/stdc++.h>

using namespace std;

constexpr long long INF = numeric_limits<long long>::max();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> uid(0ll, INF);

struct node {
	int key;
	int val;
	bool f[3][2];
	long long pry;
	int l, r;
	int prv;
};

constexpr int N = 2e5, M = 1e4 + 5;

node p[N];
int root, nd, inv[N], a[M];

inline int newnode(int _val, bool _equal, bool _incr, bool _decr, int _key = 1) {
	auto& u = p[nd++];
	u.key = _key;
	u.val = _val;
	u.f[0][1] = u.f[0][0] = _equal;
	u.f[1][1] = u.f[1][0] = _incr;
	u.f[2][1] = u.f[2][0] = _decr;
	u.pry = uid(rng);
	u.l = u.r = 0;
	u.prv = 0;
	return nd - 1;
}

inline void refresh(int t) {
	if(t == 0) return;
	
	auto& u = p[t];
	auto& l = p[u.l];
	auto& r = p[u.r];

	u.key = 1 + l.key + r.key;

	for(int i = 0; i < 3; ++i)
		u.f[i][1] = u.f[i][0] && l.f[i][1] && r.f[i][1];
}

void split(int t, int k, int& L, int& R) {
	refresh(t);
	if(t == 0) {L = R = 0; return;}
	if(p[p[t].l].key + 1 <= k) {
		split(p[t].r, k - p[p[t].l].key - 1, p[t].r, R);
		L = t;
	} else {
		split(p[t].l, k, L, p[t].l);
		R = t;
	}
	refresh(t);
}

int merge(int t1, int t2) {
	refresh(t1);
	refresh(t2);
	if(t1 == 0 || t2 == 0) return t2 != 0 ? t2 : t1;
	if(p[t1].pry < p[t2].pry) {
		p[t2].l = merge(t1, p[t2].l);
		refresh(t2);
		return t2;
	}
	p[t1].r = merge(p[t1].r, t2);
	refresh(t1);
	return t1;
}

void heapfy(int t) {
	if(t == 0) return;
	int u = t;
	if(p[t].l != 0 && p[p[t].l].pry > p[u].pry) u = p[t].l;
	if(p[t].r != 0 && p[p[t].r].pry > p[u].pry) u = p[t].r;
	if(u != t) {
		swap(p[t].pry, p[u].pry);
		heapfy(u);
	}
}

int build(int a[], int lo, int hi) {
	if(lo > hi) return 0;

	int m = (lo + hi) >> 1;
	
	inv[m] = newnode(a[m], m && a[m - 1] == a[m], m && a[m-1] <= a[m],m && a[m-1] >= a[m]);
	p[inv[m]].l = build(a, lo, m - 1);
	p[inv[m]].r = build(a, m + 1, hi);
	
	if(m) p[inv[m]].prv = inv[m - 1];
	
	refresh(inv[m]);
	heapfy(inv[m]);
	
	return inv[m];
}

inline void build(int a[], int n) {
	nd = 0;
	newnode(0, true, true, true, 0);
	root = build(a, 0, n - 1);
}

inline int query(int l, int r) {	
	int a, b, c, ans = 3;

	split(root, l, a, b);
	split(b, r - l, b, c);
	
	for(int i = 0; i < 3; ++i) {
		if(p[b].f[i][1]) {
			ans = i;
			break;
		}
	}

	root = merge(a, merge(b, c));
	return ans;
}

inline int find(int k) {
	int a, b, c;
	split(root, k - 1, a, b);
	split(b, 1, b, c);
	root = merge(a, merge(b, c));
	return b;
}

void fix(int k) {
	auto fixit = [](auto& self, int t, int k) -> void {
		if(!t) return;
		else if(p[p[t].l].key + 1 == k) {
			auto& A = p[t];
			auto& B = p[A.prv];

			A.f[0][0] = A.prv && A.val == B.val;
			A.f[1][0] = A.prv && B.val <= A.val;
			A.f[2][0] = A.prv && B.val >= A.val;

		} else if(p[p[t].l].key + 1 > k)
			self(self, p[t].l, k);
		else 
			self(self, p[t].r, k - p[p[t].l].key - 1);

		refresh(t);
	};
	
	fixit(fixit, root, k);
}

inline void swap_places(int i, int j) {
	if(i > j) swap(i, j);
	int a = find(i), b = find(j);
	swap(p[a].val, p[b].val);
	fix(i); fix(i + 1); fix(j); fix(j + 1);
}

inline void add(int k, int v) {
	int a, b, c = newnode(v, 0, 0, 0);
	split(root, k - 1, a, b);
	root = merge(merge(a, c), b);
	if(int d = find(k + 1)) p[d].prv = c;
	p[c].prv = find(k - 1);
	fix(k); fix(k + 1);
}

inline void upd(int k, int v) {
	int a = find(k);
	p[a].val = v;
	fix(k); fix(k + 1);
}

inline void rem(int k) {
	int a, b, c;
	split(root, k - 1, a, b);
	split(b, 1, b, c);
	root = merge(a, c);
	if(int d = find(k)) p[d].prv = p[b].prv;	
	fix(k);
}

const char* info[] = {"ALL EQUAL", "NON DECREASING", "NON INCREASING", "NONE"};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int n, q;

	while(cin >> n) {
		for(int i = 0; i < n; ++i)
			cin >> a[i];

		build(a, n);

		cin >> q;
		
		while(q-- > 0) {
			int t, x, y;
			cin >> t >> x;

			if(t == 0) {cin >> y; swap_places(x, y);}
			else if(t == 1) {cin >> y; upd(x, y);}
			else if(t == 2) {cin >> y; add(x, y);}
			else if(t == 3) rem(x);
			else {cin >> y; cout << info[query(x, y)] << '\n';}
		}
	}

	return 0;
}