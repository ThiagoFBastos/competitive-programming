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
 
namespace factorization {
 
	template<class T>
	T modMul(T a, T b, T m) {
		return (T)((__int128)a * b % m);
	}
 
	template<class T>
	T modMulExp(T a, T p, T m) {
		T ans = 1;
		for(; p > 0; p >>= 1) {
			if(p & 1) ans = modMul(ans, a, m);
			a = modMul(a, a, m);
		}
		return ans;
	}
 
	template<class T>
	bool miller(T n) {
		const int pn = 9;
		const T p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
 
		for(T k : p)
			if(n % k == 0)
				return n == k;
		
		if(n < p[pn - 1]) return false;
 
		T t = n - 1;
		int s = 0;
 
		while(~t & 1) t >>= 1, ++s;
 
		for(T k : p) {
			T pt = modMulExp(k, t, n);
 
			if(pt == 1) continue;
 
			bool ok = false;
 
			for(int j = 0; j < s && !ok; ++j) {
				ok = ok || pt == n - 1;
				pt = modMul(pt, pt, n);
			}
 
			if(!ok) return false;
		}
 
		return true;
	}
 
	template<class T>
	T f(T x, T c, T mod) {
		return (modMul(x, x, mod) + c) % mod;
	}
 
	template<class T>
	T rho(T n) {
		mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
		T x, y, g = n;
		while(g == n) {
			T x0 = rnd(), c = rnd();
			x = y = x0;
			g = 1;
			while(g == 1) {
				x = f(x, c, n);
				y = f(f(y, c, n), c, n);
				g = gcd(abs(x - y), n);
			}
		}
		return g;
	}
	
	template<class T>
	vector<pair<T, int>> factorize(T n) {	
		vector<pair<T, int>> f;
		
		if(~n & 1) {
			int k = 0;
			while(~n & 1) {
				n >>= 1;
				++k;
			}

			f.emplace_back(2, k);
		}

		for(T p = 3; p * p * p * p <= n; p += 2) {
			if(n % p) continue;
			int i = 0;
			while(n % p == 0) n /= p, ++i;
			f.pb({p, i});
		}

		while(n != 1) {
			if(miller(n)) {
				f.pb({n, 1});
				break;
			}
			
			T k = rho(n);
			
			if(!miller(k))
				k = rho(k);

			int i = 0;
			while(n % k == 0) n /= k, ++i;
			f.pb({k, i});
		}
		return f;
	}
};
 
void solve() {
	int q;

	cin >> q;

	while(q-- > 0) {
		i64 n;
 
		cin >> n;
 
		auto f = factorization :: factorize(n);
 
		sort(all(f));
 
		auto power = f | views::transform([](auto p) { return p.second;});

		int size = accumulate(ranges::begin(power), ranges::end(power), 0);

		cout << size;

		for(auto [p, k] : f) {
			while(k-- > 0)
				cout << ' ' << p;
		}

		cout << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
} 
