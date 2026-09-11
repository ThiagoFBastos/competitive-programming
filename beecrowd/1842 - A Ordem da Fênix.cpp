#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5 + 10;
int p[maxn], c[maxn], pt[maxn], ct[maxn], cnt[maxn], prefixo[maxn], inv[maxn];

void suffix_array(string& s) {
	s += '#';
	int n = s.size();
	memset(cnt, 0, 128 * sizeof(int));
	for(char ch : s) ++cnt[ch + 1];
	for(int k = 1; k < 128; ++k) cnt[k] += cnt[k - 1];
	for(int k = 0; k < n; ++k) p[cnt[s[k]]++] = k;
	c[p[0]] = 0;
	for(int k = 1; k < n; ++k) c[p[k]] = c[p[k - 1]] + (s[p[k]] != s[p[k - 1]]);
	int tot = c[p[n - 1]] + 1;
	for(int i = 0; (1 << i) <= n; ++i) {
		memset(cnt, 0, tot * sizeof(int));
		for(int k = 0; k < n; ++k) {
			int j = p[k] - (1 << i);
			if(j < 0) j += n;
			++cnt[c[j] + 1];
		}
		for(int k = 1; k < tot; ++k) cnt[k] += cnt[k - 1];
		for(int k = 0; k < n; ++k) {
			int j = p[k] - (1 << i);
			if(j < 0) j += n;
			pt[cnt[c[j]]++] = j;
		}
		memcpy(p, pt, n * sizeof(int));
		tot = 0;
		ct[p[0]] = 0;
		for(int k = 1; k < n; ++k) {
			int A = p[k], B = p[k] + (1 << i), C = p[k - 1], D = p[k - 1] + (1 << i);
			if(B >= n) B -= n;
			if(D >= n) D -= n;
			tot += c[A] != c[C] || c[B] != c[D];
			ct[p[k]] = tot;
		}
		++tot;
		memcpy(c, ct, n * sizeof(int));
	}
	s.pop_back();
	for(int k = 1; k < n; ++k) p[k - 1] = p[k];
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int k = 0, n;
	cin >> s;
	n = s.size();
	suffix_array(s);
	for(int k = 0; k < n; ++k) inv[p[k]] = k;
	for(int i = 0; i < n; ++i) {
		if(inv[i] == 0) 
			prefixo[i] = 0;
		else {
			int j = p[inv[i] - 1], h = k;
			while(h + max(j, i) < n && s[h + i] == s[h + j]) ++h;
			prefixo[i] = h;
			k = max(0, h - 1);
		}
	}
	ii ans = {0, 0};
	for(int i = 0; i < n; ++i) ans = max(ans, make_pair(prefixo[i], -i));
	if(ans.first < 3) cout << "*\n";
	else cout << s.substr(-ans.second, ans.first) << '\n';
  	return 0;
}