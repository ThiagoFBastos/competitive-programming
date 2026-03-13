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

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	n %= m;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}

template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int v) : val {v} {}
	modInt(i64 v) : val {int((v%m+m)%m)} {}

	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
	}
	
	modInt& operator^=(i64 p) {
		val = exp(val, p, m);
		return *this;
	}

	modInt operator+(modInt x) {
		int ans = val + x.val;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(modInt x) {
		int ans = val - x.val;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return {int(((i64)val * x.val % m + m) % m)};
	}

	modInt& operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {int((val * exp(x.val, m - 2, m) % m + m) % m)};
	}
	
	modInt& operator/=(modInt x) {
		val = (val * exp(x.val, m - 2, m) % m + m) % m;
		return *this;
	}
	
	modInt operator+(i64 x) {
		x = (x % m + m) % m;
		int ans = val + x;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(i64 x) {
		x = (x % m + m) % m;
		int ans = val - x;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(i64 x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(i64 x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(i64 x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt& operator*=(i64 x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(i64 x) {
		return {int(val * exp(x, m - 2, m) % m)};
	}
	
	modInt& operator/=(i64 x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}

	bool operator==(modInt other) {
		return val == other.val;
	}

	bool operator!=(modInt other) {
		return val != other.val;
	}

	friend ostream& operator<<(ostream& os, modInt v) {
		os << v.val;
		return os;
	}

	friend istream& operator>>(istream& is, modInt& v) {
		i64 x;
		is >> x;
		v.val = (x % m + m) % m; 
		return is;
	}

	friend modInt operator+(i64 x, modInt other) {
		return other + x;
	}

	friend modInt operator-(i64 x, modInt other) {
		return modInt{x} - other;
	}

	friend modInt operator*(i64 x, modInt other) {
		return other * x;
	}

	friend modInt operator/(i64 x, modInt other) {
		return modInt{x} / other;
	}
};

const int N = 11, MOD = 998244353;

using modint = modInt<MOD>;

modint dp[2][N][N][N];

void solve() {
	int n, m;

	cin >> n >> m;

	dp[0][m][m][m] = 1;
	
	for(int i = 0; i < n; ++i) {

		for(int a = 0; a <= m; ++a)
			for(int b = 0; b <= m; ++b)
				for(int c = 0; c <= m; ++c)
					dp[1][a][b][c] = 0;

		for(int x = 0; x < m; ++x) {
			for(int a = x; a <= m; ++a) {
				for(int b = 0; b <= m; ++b) {
					for(int c = 0; c <= m; ++c) {
						int p = min(a, x > b ? x : m);		
						int q = min(b, x > c ? x : m);
						int r = min(c, x);
						dp[1][p][q][r] += dp[0][a][b][c];
					}
				}
			}
		}

		for(int a = 0; a <= m; ++a)
			for(int b = 0; b <= m; ++b)
				for(int c = 0; c <= m; ++c)
					dp[0][a][b][c] = dp[1][a][b][c];
	}

	modint ans;
	
	for(int a = 0; a < m; ++a)
		for(int b = 0; b <= m; ++b)
			for(int c = 0; c <= m; ++c)
				ans += dp[0][a][b][c];

	cout << ans << '\n';
}			

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
