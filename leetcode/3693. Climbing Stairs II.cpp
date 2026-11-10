class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        constexpr int INF = 1e9;
        vector<int> dp(n + 1, INF);

        dp[0] = 0;

        for(int i = 0; i < n; ++i) {
            for(int j = 1; j <= 3 && i + j <= n; ++j) {
                const int step = j * j;
                const int nxt = i + j;
                dp[nxt] = min(dp[nxt], dp[i] + costs[nxt - 1] + step);
            }
        }

        return dp.back();
    }
};