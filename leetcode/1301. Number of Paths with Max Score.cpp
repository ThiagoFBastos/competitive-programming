class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        constexpr int MOD = 1'000'000'007;
        constexpr int INF = 1'000'000'000;
        const int n = static_cast<int>(board.size());
        const int m = static_cast<int>(board[0].size());

        using value_type = pair<int, int>;

        vector<vector<value_type>> dp(n + 1, vector<value_type>(m + 1, value_type {-INF, 0}));

        value_type delta[] = {{1, 0}, {0, 1}, {1, 1}};

        dp[n - 1][m - 1] = {0, 1};
        dp[0][0] = {0, 0};

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {

                if(board[i][j] == 'X')
                    continue;

                const int value = isdigit(board[i][j]) ? board[i][j] - '0' : 0;

                auto best = make_pair(-INF, 0);

                for(const auto [dx, dy] : delta) {
                    const int x = i + dx, y = j + dy;

                    if(dp[x][y].first < 0)
                        continue;

                    const int sum = value + dp[x][y].first;

                    if(dp[i][j].first == sum)
                        dp[i][j].second += dp[x][y].second;
                    else if(dp[i][j].first < sum)
                        dp[i][j] = {sum, dp[x][y].second};

                    if(dp[i][j].second >= MOD)
                        dp[i][j].second -= MOD;
                }
            }
        }

        return {dp[0][0].first, dp[0][0].second};
    }
};