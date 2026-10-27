#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <class K, class V>
using ht = gp_hash_table
<K, V, std :: hash<K>, std :: equal_to<K>,
direct_mask_range_hashing<>,
linear_probe_fn<>,
hash_standard_resize_policy<
hash_exponential_size_policy<>,
hash_load_check_resize_trigger
<>, true>>;
 
 long long uniform(long long l, long long r) {
	return 148762884;
}

template<class T, int k>
struct MersenneHash {
	static long long P;
	static constexpr long long mod = (1ll << k) - 1;
	vector<long long> invp, h;

	MersenneHash() = default;

	MersenneHash(const T& s) : invp(s.size() + 1), h(s.size() + 1) {
		const int n = static_cast<int>(s.size());

        const long long INVP = binExp(P, mod - 2);
        long long p = 1;
        
		invp[0] = 1;
        h[0] = 0;

		for(int i = 1; i <= n; ++i) {
			p = mulmod(p, P);
            invp[i] = mulmod(invp[i - 1], INVP);
			h[i] = addmod(h[i - 1], mulmod(p, s[i - 1]));
		}
	}

    long long binExp(long long n, long long p) {
        long long answer {1};

        for(; p > 0; p >>= 1) {
            if(p & 1)
                answer = mulmod(answer, n);
            n = mulmod(n, n);
        }

        return answer;
    }

	long long addmod(long long a, long long b) const {
		a += b;
		return a >= mod ? a - mod : a;
	}

	long long mulmodSQRT(long long a, long long b) const {
		return addmod((a*b) & mod, (a*b) >> k);
	}
	
	long long mulmod(long long a, long long b) const {
		int m1 = (k + 1) >> 1, m2 = k >> 1;
		long long a1 = a >> m1, a2 = a & ((1ll << m1) - 1), b1 = b >> m2, b2 = b & ((1ll << m2) - 1);
		long long s = mulmodSQRT(a1, b1), t = mulmodSQRT(a1, b2);
		long long u = mulmodSQRT(b1, a2), v = mulmodSQRT(a2, b2);
		t = addmod((t & ((1ll<<m2)-1)) << m1, t >> (k - m1));
		u = addmod((u & ((1ll<<m1)-1)) << m2, u >> (k - m2));
		return addmod(addmod(s, t), addmod(u, v));
	}

	long long operator()(int l, int r) const {
		return mulmod(addmod(h[r + 1] - h[l], mod), invp[l]);
	}
};

template<class T, int k>
long long MersenneHash<T, k> :: P = uniform(256, (1ll << k) - 2);

class Solution {
public:
    int numOfPairs(vector<string>& nums, string target) {
        ht<long long, int> hash2cnt;

        auto add = [&](long long h) {
            if(auto it = hash2cnt.find(h); it != hash2cnt.end())
                ++it->second;
            else
                hash2cnt[h] = 1;
        };

        auto rem = [&](long long h) {
            auto it = hash2cnt.find(h);
            --it->second;
        };

        for(const auto& s : nums) {
            MersenneHash<string, 61> mh(s);
            const int n = static_cast<int>(s.size());
            add(mh(0, n - 1));
        }

        int pairs {};
        MersenneHash<string, 61> mhTarget(target);
        const int m = static_cast<int>(target.size());

        for(const auto& s : nums) {
            const int n = static_cast<int>(s.size());

            if(n >= m)
                continue;

            MersenneHash<string, 61> mh(s);
            const auto h = mh(0, n - 1);
            
            if(h != mhTarget(0, n - 1))
                continue;

            rem(h);

            const auto current = mhTarget(n, m - 1); 

            if(auto it = hash2cnt.find(current); it != hash2cnt.end())
                pairs += it->second;

            add(h);
        }

        return pairs;
    }
};