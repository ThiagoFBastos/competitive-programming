#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

vector<int> z_function(string& s) {
    int n = (int)s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[n - z[i] - 1] == s[n - i - z[i] - 1]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve() {
	int n, ans = 0;
	string s;
	cin >> n >> s;
	for(int i = 0; i < n; ++i) {
		auto z = z_function(s);
		int m = s.size();
		for(int i = m - 1; i >= 0; --i)
			ans = max(ans, min(z[m - i - 1], (int)s.size() - i - 1));
		s.pop_back();		
	}	
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
