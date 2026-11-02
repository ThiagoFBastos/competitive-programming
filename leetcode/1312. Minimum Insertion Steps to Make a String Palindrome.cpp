class Solution {
public:
    int minInsertions(string s) {
        const int n = static_cast<int>(s.size());
        constexpr int INF = static_cast<int>(1e9);
        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int i = 0; i < n; ++i) {
            if(i > 0)
                dp[i][i - 1] = 0;
            dp[i][i] = 0;
        }

        auto DP = [&](auto& self, const int left, const int right) -> int {            
            if(dp[left][right] != -1)
                return dp[left][right];

            dp[left][right] = INF;

            if(s[left] == s[right])
                dp[left][right] = self(self, left + 1, right - 1);

            dp[left][right] = min(dp[left][right], 1 + self(self, left + 1, right));
            dp[left][right] = min(dp[left][right], 1 + self(self, left, right - 1));

            return dp[left][right];
        };

        return DP(DP, 0, n - 1);
    }
};