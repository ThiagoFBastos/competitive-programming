#include <bits/stdc++.h>

using namespace std;

istream& operator>>(istream& is, __int128& rhs) {
	string str;

	is >> str;
	rhs = 0;

	for(char digit : str)
		rhs = 10 * rhs + digit - '0';

	return is;
}

ostream& operator<<(ostream& os, __int128 rhs) {
	string str;

	if(rhs == 0)
		str = "0";

	for(; rhs > 0; rhs /= 10) 
		str += rhs % 10 + '0';

	reverse(str.begin(), str.end());

	os << str;

	return os;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int tc = 1;

	while(true) {

		int n, f;

		cin >> n >> f;

		if(n + f == 0) break;

		vector<__int128> values(n);

		for(auto& val : values) cin >> val;

		auto sum = accumulate(values.begin(), values.end(), (__int128)0);

		cout << "Bill #" << tc++ << " costs " << sum << ": each friend should pay " << sum / f << "\n\n";
	}

	return 0;
}
