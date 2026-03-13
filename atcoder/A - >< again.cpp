#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int n;
string s;
vector<int> a;

bool divisible(int k) {
	for(int i = 1; i <= n; ++i) {	
		if(a[i - 1] / k == a[i] / k) return false;
		if(s[i - 1] == '>') {
			if(a[i - 1] % k < a[i] % k && a[i - 1] / k <= a[i] / k + 1) return false;
		} else {
			if(a[i - 1] % k > a[i] % k && a[i - 1] / k + 1 >= a[i] / k) return false;
		}
	}
	return true;
}

void solve() {	
	cin >> n >> s;
	a.resize(n + 1);
	for(int& v : a) cin >> v;
	int m = 0;
	for(int k = 16; k >= 0; --k) {
		int L = m + (1 << k);
		if(divisible(L)) m = L;
	}
	cout << m << endl;
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j <= n; ++j) cout << a[j] / m + (a[j] % m >= m - i) << ' ';
		cout << endl;
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
