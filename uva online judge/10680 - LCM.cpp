#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e6 + 5;

int mod[N], base[N], pw[N], diff[N];
bitset<N> is_prime;

int power(int n, int k) {
	int i = 0;
	while(n > 0 && n % k == 0) n /= k, ++i;
	return i;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	for(int i = 1; i < N; ++i) {
		is_prime[i] = 1;
		mod[i] = 1;
	}

	for(int i = 2; i < N; ++i) {
		if(!is_prime[i])
			continue;

		long long n = i;

		while(n < N) {
			mod[n] = n;
			base[n] = i;
			n *= i;
		}

		for(int j = i; j < N; j += i)
			is_prime[j] = 0;
	}

	mod[1] = 1;

	auto bin_exp = [](long long n, long long p, long long mod) {
		auto result = 1ll;

		for(; p > 0; p >>= 1) {
			if(p & 1) result = result * n % mod;
			n = n * n % mod;
		}

		return result;
	};

	for(int i = 2; i < N; ++i) {
		auto increase = mod[i] / max(1, pw[base[i]]);

		pw[base[i]] = mod[i];
		diff[i] = power(pw[2], 2) - power(pw[5], 5);

		if(base[i] == 2 || base[i] == 5) increase = 1;

		mod[i] = max<long long>(1, increase) * mod[i - 1] % 10;
	}

	while(true) {
		int n;

		cin >> n;

		if(!n) break;

		auto answer = mod[n] * bin_exp(2, diff[n], 10) % 10;

		cout << answer << '\n';
	}
	
	return 0;
} 
