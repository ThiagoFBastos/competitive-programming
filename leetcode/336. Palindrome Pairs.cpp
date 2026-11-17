mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
long long uniform(long long l, long long r) {
	uniform_int_distribution<long long> uid(l, r);
	return uid(rng);
}

template<class T, int k>
struct MersenneHash {
	static long long B;
    static long long BINV;
	static constexpr long long mod = (1ll << k) - 1;
	vector<long long> inv_pow, hash;

	MersenneHash() {}
	MersenneHash(const T& s) 
        : inv_pow(s.size() + 1)
        , hash(s.size() + 1) 
    {
        long long pow = 1;

		inv_pow[0] = 1, hash[0] = 0;
		for(int i = 1; i <= (int)s.size(); ++i) {
			pow = mulmod(pow, B);
            inv_pow[i] = mulmod(inv_pow[i - 1], BINV);
			hash[i] = addmod(hash[i - 1], mulmod(pow, s[i - 1]));
		}
	}

    static long long inverse(long long x) {
        long long ans = 1;

        for(auto i = mod - 2; i; i >>= 1) {
            if(i & 1)
                ans = mulmod(ans, x);
            x = mulmod(x, x);
        }

        return ans;
    }

	static long long addmod(long long a, long long b) {
		a += b;
		return a >= mod ? a - mod : a;
	}

	static long long mulmodSQRT(long long a, long long b) {
		return addmod((a * b) & mod, (a * b) >> k);
	}
	
	static long long mulmod(long long a, long long b) {
		int m1 = (k + 1) >> 1, m2 = k >> 1;
		long long a1 = a >> m1, a2 = a & ((1ll << m1) - 1), b1 = b >> m2, b2 = b & ((1ll << m2) - 1);
		long long s = mulmodSQRT(a1, b1), t = mulmodSQRT(a1, b2);
		long long u = mulmodSQRT(b1, a2), v = mulmodSQRT(a2, b2);
		t = addmod((t & ((1ll<<m2)-1)) << m1, t >> (k - m1));
		u = addmod((u & ((1ll<<m1)-1)) << m2, u >> (k - m2));
		return addmod(addmod(s, t), addmod(u, v));
	}

	long long operator()(int l, int r) {
		return mulmod(addmod(hash[r + 1] - hash[l], mod), inv_pow[l]);
	}
};

template<class T, int k>
long long MersenneHash<T, k> :: B = 579835928768LL;

template<class T, int k>
long long MersenneHash<T, k> :: BINV = MersenneHash<T, k>::inverse(MersenneHash<T, k> :: B);

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<long long, vector<int>> hash2posleft, hash2posright;
        vector<vector<int>> pairs;
        unordered_set<int> palindromes;
        int empty_index = -1;

        for(size_t i = 0; i < words.size(); ++i) {
            if(words[i].empty()) {
                empty_index = static_cast<int>(i);
                continue;
            }

            string rev(words[i].rbegin(), words[i].rend());

            MersenneHash<string, 61> mersenne1(rev), mersenne2(words[i]);

            if(mersenne1(0, rev.size() - 1) == mersenne2(0, rev.size() - 1))
                palindromes.insert(i);

            for(size_t j = 1; j <= rev.size(); ++j) {
                size_t n = rev.size() - j;
                bool is_prefix_palindrome = false;

                if(n <= 1)
                    is_prefix_palindrome = true;
                else {
                    auto mid = n / 2;

                    int l1 = 0, r1 = mid - 1;
                    int l2 = mid + n % 2, r2 = n - 1;

                    auto h1 = mersenne2(l1, r1);
                    auto h2 = mersenne1(rev.size() - r2 - 1, rev.size() - l2 - 1);

                    is_prefix_palindrome = h1 == h2;
                }

                if(is_prefix_palindrome) {
                    auto h = mersenne1(0, j - 1);
                    hash2posright[h].push_back(static_cast<int>(i));
                }
            }

            for(size_t j = 1; j < rev.size(); ++j) {
                size_t n = rev.size() - j;
                bool is_prefix_palindrome = false;

                if(n <= 1)
                    is_prefix_palindrome = true;
                else {
                    auto mid = n / 2;

                    int l1 = 0, r1 = mid - 1;
                    int l2 = mid + n % 2, r2 = n - 1;

                    auto h1 = mersenne1(l1, r1);
                    auto h2 = mersenne2(rev.size() - r2 - 1, rev.size() - l2 - 1);

                    is_prefix_palindrome = h1 == h2;
                }

                if(is_prefix_palindrome) {
                    auto h = mersenne1(rev.size() - j, rev.size() - 1);
                    hash2posleft[h].push_back(static_cast<int>(i));
                    
                }
            }
        }

        for(size_t i = 0; i < words.size(); ++i) {
            if(words[i].empty()) {
                for(auto j : palindromes)
                    pairs.push_back({static_cast<int>(i), j});
                continue;
            }

            MersenneHash<string, 61> mersenne(words[i]);

            if(auto it = hash2posleft.find(mersenne(0, words[i].size() - 1)); it != hash2posleft.end()) {
                for(auto j : it->second) {
                    if(i != j)
                        pairs.push_back({j, static_cast<int>(i)});
                }
            }

            if(auto it = hash2posright.find(mersenne(0, words[i].size() - 1)); it != hash2posright.end()) {
                for(auto j : it->second) {
                    if(i != j)
                        pairs.push_back({static_cast<int>(i), j});
                }
            }

            if(auto j = empty_index; j != -1 && palindromes.count(i))
                pairs.push_back({static_cast<int>(i), j});
        }

        sort(pairs.begin(), pairs.end());
        pairs.erase(unique(pairs.begin(), pairs.end()), pairs.end());

        return pairs;
    }
};