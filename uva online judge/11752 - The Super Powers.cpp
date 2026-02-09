#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1 << 16;

bitset<64> is_prime;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	is_prime.set();

    for(int p = 2; p * p <= 64; ++p) {
        if(is_prime[p])
            for(int i = 2 * p; i <= 64; i += p)
                is_prime[i] = 0;
    }

    set<unsigned long long> super_powers {1};
	unsigned __int128 lim = numeric_limits<unsigned long long>::max();

    for(int i = 2; i < N; ++i) {
        unsigned __int128 number = (unsigned __int128)i * i * i * i;

        for(int j = 4; number <= lim; ++j) {
            if(!is_prime[j]) super_powers.insert((unsigned long long)number);
            number *= i;
        }
    }

    for(auto number : super_powers)
        cout << number << '\n';

	return 0;
}
