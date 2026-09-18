class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        constexpr int ALPHA = 26;
        constexpr int INF = numeric_limits<int>::max();
        const int n = static_cast<int>(s.size());
        array<int, ALPHA> first, last, freq;

        first.fill(INF);
        last.fill(-1);
        freq.fill(0);

        for(int i = 0; i < n; ++i) {
            int ord = static_cast<int>(s[i] - 'a');
            first[ord] = min(first[ord], i);
            last[ord] = max(last[ord], i);
            ++freq[ord];
        }

        auto chars = views::iota(0, 26) | views::filter([&first](int ord) {
            return first[ord] != INF;
        }) | ranges::to<vector<int>>();

        sort(chars.begin(), chars.end(), [&first](int lhs, int rhs) {
            return first[lhs] < first[rhs];
        });

        const int m = static_cast<int>(chars.size());
        vector<int> dp(m + 1, -INF);
        vector<vector<string>> solutions(m + 1);

        dp[m] = 0;

        for(int i = m - 1; i >= 0; --i) {
            int ord = chars[i];
            int last_pos = last[ord], hi = i, cnt = freq[ord];

            while(hi + 1 < m && last_pos > first[chars[hi + 1]]) {
                cnt += freq[chars[hi + 1]];
                last_pos = max(last_pos, last[chars[hi + 1]]);
                ++hi;
            }
            
            dp[i] = dp[i + 1];
            solutions[i] = solutions[i + 1];

            if(cnt == last_pos - first[ord] + 1 && dp[i] < dp[hi + 1] + 1) {
                dp[i] = dp[hi + 1] + 1;
                solutions[i] = solutions[hi + 1];
                solutions[i].push_back(s.substr(first[ord], last_pos - first[ord] + 1));
            }
        }

        auto index = max_element(dp.begin(), dp.end()) - dp.begin();

        return solutions[index];
    }
};