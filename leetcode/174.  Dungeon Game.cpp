class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        const int n = static_cast<int>(dungeon.size());
        const int m = static_cast<int>(dungeon[0].size());
        constexpr int INF = 1e9;

        auto check = [&](int health) {
            vector<vector<int>> dp(n + 1, vector<int>(m + 1, -INF));

            dp[1][0] = health;

            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= m; ++j) {
                    dp[i][j] = dungeon[i - 1][j - 1] + max(dp[i - 1][j], dp[i][j - 1]);
                    if(dp[i][j] <= 0)
                        dp[i][j] = -INF;
                }
            }

            return dp[n][m] > 0;
        };

        int low = 1, high = INF;

        while(low < high) {
            int mid = (low + high) / 2;

            if(check(mid))
                high = mid;
            else
                low = mid + 1;
        }

        return high;
    }
};