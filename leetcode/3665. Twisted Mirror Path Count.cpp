class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        constexpr int MOD = 1'000'000'007;
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());
        constexpr pair<int, int> delta[] = {{0, 1}, {1, 0}};

        using value_type = array<int, 2>;
        vector<vector<value_type>> dp(n + 1, vector<value_type>(m + 1, value_type {-1, -1}));

        dp[n - 1][m - 1][0] = 1;
        dp[n - 1][m - 1][1] = 1;
        
        auto dfs = [&](auto& self, const int x, const int y, const int px, const int py) -> int {
            if(x >= n || y >= m)
                return 0;

            int side = y - py == 1 ? 0 : 1;

            if(dp[x][y][side] != -1)
                return dp[x][y][side];

            else if(grid[x][y]) {
                if(side == 0)
                    dp[x][y][side] = self(self, x + 1, y, x, y);
                else
                    dp[x][y][side] = self(self, x, y + 1, x, y);

                return dp[x][y][side];
            }

            return dp[x][y][side] = (self(self, x + 1, y, x, y) + self(self, x, y + 1, x, y)) % MOD;
        };

        const int answer = (dfs(dfs, 0, 1, 0, 0) + dfs(dfs, 1, 0, 0, 0)) % MOD;

        return answer;
    }
};