mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
long long uniform(long long l, long long r) {
	uniform_int_distribution<long long> uid(l, r);
	return uid(rng);
}

long long binExp(long long n, long long p, long long m) {
    long long ans = 1;

    for(; p > 0; p >>= 1) {
        if(p & 1)
            ans = (__int128)ans * n % m;
        n = (__int128)n * n % m;
    }

    return ans;
}

struct Hash {
    static constexpr long long MOD = (1LL << 61) - 1;
    static const long long B;
    static const unordered_map<char, long long> ch2id;

    vector<long long> prefix;

    Hash(const string& s) {
        const int n = static_cast<int>(s.size());

        prefix.resize(n + 1);
        prefix[0] = 0;

        for(int i = 1; i <= n; ++i) {
            const char ch = s[i - 1];
            prefix[i] = (prefix[i - 1] + ch2id.at(ch)) % MOD;
        }
    }

    long long operator()(int l, int r) {
        auto h = prefix[r + 1] - prefix[l];

        if(h < 0)
            h += MOD;

        return h;
    }
};

const long long Hash::B = uniform(256, Hash::MOD - 2);

const unordered_map<char, long long> Hash::ch2id = views::iota('a', static_cast<char>('z' + 1)) | views::transform([](const char ch) {
    return make_pair(ch, binExp(Hash::B, uniform(256, Hash::MOD - 2), Hash::MOD));
}) | ranges::to<unordered_map<char, long long>>();

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        Hash hs(s);
        vector<int> answer;

        const int n = static_cast<int>(s.size());
        const int m = static_cast<int>(p.size());

        auto hp = Hash(p)(0, m - 1);

        answer.reserve(max(1, n - m + 1));

        for(int i = 0; i <= n - m; ++i) {
            if(hs(i, i + m - 1) == hp)
                answer.push_back(i);
        }

        return answer;
    }
};