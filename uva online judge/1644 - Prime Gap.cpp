#include <bits/stdc++.h>

using namespace std;

namespace factorization
{ 
    /**
     * @brief take the modulo of the mutiplication of two numbers
     * @param a a number
     * @param b a number
     * @param m the modulo
     */
	template<class T>
	T modMul(T a, T b, T m)
	{
		return (T)((__int128)a * b % m);
	}
 
    /**
     * @brief modular binary exponetiation
     * @param a the base number
     * @param p the power
     * @param m the modulo
     */
	template<class T>
	T modMulExp(T a, T p, T m)
	{
		T ans = 1;
		for(; p > 0; p >>= 1) 
		{
			if(p & 1) ans = modMul(ans, a, m);
			a = modMul(a, a, m);
		}
		return ans;
	}
 
    /**
     * Miller-Rabin algorithm to check wheather a number is prime
     * @param n the target number
     * @return true if the number is prime, and false otherwise
     */
	template<class T>
	bool miller(T n)
	{
		const int pn = 9;
		const T p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
 
		for(T k : p)
			if(n % k == 0)
				return n == k;
		
		if(n < p[pn - 1]) return false;
 
		T t = n - 1;
		int s = 0;
 
		while(~t & 1) t >>= 1, ++s;
 
		for(T k : p)
		{
			T pt = modMulExp(k, t, n);
 
			if(pt == 1) continue;
 
			bool ok = false;
 
			for(int j = 0; j < s && !ok; ++j)
			{
				ok = ok || pt == n - 1;
				pt = modMul(pt, pt, n);
			}
 
			if(!ok) return false;
		}
 
		return true;
	}
 
    /**
     * auxiliar function used in the rho method
     * @param x the number to square up
     * @param c the linear coefficient
     * @param mod the number to take the modulo of the function
     * @return (x^2 + c) % mod
     */
	template<class T>
	T f(T x, T c, T mod)
	{
		return (modMul(x, x, mod) + c) % mod;
	}
 
    /**
     * Pollard-Rho algorithm to find a factor of n
     * @param n the target number
     * @return a factor of n != 1, n (cannot be called for prime numbers)
     */
	template<class T>
	T rho(T n)
	{
		std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
		T x, y, g = n;

		while(g == n)
		{
			T x0 = rnd(), c = rnd();
			x = y = x0;
			g = 1;

			while(g == 1)
			{
				x = f(x, c, n);
				y = f(f(y, c, n), c, n);
				g = __gcd(abs(x - y), n);
			}
		}

		return g;
	}
	
    /**
     * Factorize a number using the pollard-rho algorithm and a brute force of
     * prime numbers until n^(1 / 4)
     * @param n the target number
     * @return a vector of factors as (p, k), ie, p^k
     */
	template<class T>
	std::vector<std::pair<T, int>> factorize(T n)
	{	
		std::vector<std::pair<T, int>> f;
		
		if(~n & 1)
		{
			int k = 0;

			while(~n & 1)
			{
				n >>= 1;
				++k;
			}

			f.emplace_back(2, k);
		}

		for(T p = 3; p * p * p * p <= n; p += 2)
		{
			if(n % p) continue;

			int i = 0;
			while(n % p == 0) n /= p, ++i;
			f.emplace_back(p, i);
		}

		while(n != 1)
		{
			if(miller(n))
			{
				f.emplace_back(n, 1);
				break;
			}
			
			T k = rho(n);
			
			if(!miller(k))
				k = rho(k);

			int i = 0;
			while(n % k == 0) n /= k, ++i;
			f.emplace_back(k, i);
		}

		return f;
	}
}

int next_prime(int n) {
	while(!factorization::miller(n)) ++n;
	return n;
}

int previous_prime(int n) {
	while(!factorization::miller(n)) --n;
	return n;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	while(true) {
		int n;

		cin >> n;

		if(!n) break;

		if(factorization::miller(n))
			cout << "0\n";
		else
			cout << next_prime(n) - previous_prime(n) << '\n';
	}
	
	return 0;
} 
