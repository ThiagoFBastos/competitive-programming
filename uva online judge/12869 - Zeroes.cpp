#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	while(true) {
		int64_t low, high;

		cin >> low >> high;

		if(low == 0 && high == 0) break;

		auto cnt = high / 5 - (low - 1) / 5;

		if(low % 5) ++cnt;

		cout << cnt << '\n';
	}

	return 0;
}
