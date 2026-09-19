#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	using map_key_type = pair<long long, int>;

	map<map_key_type, int> frq;

	int n;
	long long k;

	cin >> n >> k;

	long long mod_sum = 0, cnt = 0;
	int odd_even_diff = 0;

	frq[{0, 0}] = 1;

	for(int i = 0; i < n; ++i) {
		long long value;

		cin >> value;

		mod_sum = (mod_sum + value) % k;
		odd_even_diff += value % 2 ? -1 : 1;

		if(auto it = frq.find(make_pair(mod_sum, odd_even_diff)); it != frq.end())
			cnt += it->second;

		++frq[{mod_sum, odd_even_diff}];
	}

	cout << cnt << '\n';

	return 0;
}