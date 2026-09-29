class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        constexpr int N = 100;
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());

        auto dp = vector<vector<bitset<N>>>(n + 1, vector<bitset<N>>(m + 1));

        dp[1][0][0] = 1;

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                const char ch = grid[i - 1][j - 1];

                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];

                if(ch == '(')
                    dp[i][j] <<= 1;
                else
                    dp[i][j] >>= 1;
            }
        }

        return static_cast<bool>(dp[n][m][0]);
    }
};