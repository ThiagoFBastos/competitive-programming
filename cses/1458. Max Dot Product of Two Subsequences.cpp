class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        const int n = static_cast<int>(nums1.size());
        const int m = static_cast<int>(nums2.size());
        constexpr int INF = 1e9;

        vector<vector<int>> dp(n + 2, vector<int>(m + 2, -INF));

        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= m; ++j) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);

                if(i < n && j < m)
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], max(0, dp[i][j]) + nums1[i] * nums2[j]);
            }
        }

        return dp[n][m];
    }
};