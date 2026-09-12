class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        const auto n = str1.size();
        const auto m = str2.size();
        constexpr int INF = 1e9;

        vector<vector<int>> dp(n + 2, vector<int>(m + 2, INF));

        dp[0][0] = 0;

        for(size_t i = 0; i <= n; ++i) {
            for(size_t j = 0; j <= m; ++j) {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);

                if(str1[i] == str2[j])
                    dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
            }
        }

        int length = dp[n][m];
        size_t i = n, j = m;
        string answer;

        answer.reserve(length);
        
        while(i || j) {
            if(i > 0 && j > 0) {
                if(str1[i - 1] == str2[j - 1] && length == dp[i - 1][j - 1] + 1) {
                    --length;
                    answer += str1[i - 1];
                    --i, --j;
                } else if(length == dp[i - 1][j] + 1) {
                    --length;
                    answer += str1[--i];
                } else if(length == dp[i][j - 1] + 1) {
                    --length;
                    answer += str2[--j];
                } else {
                    assert(false);
                }
            } else if(i > 0) {
                if(length == dp[i - 1][j] + 1) {
                    --length;
                    answer += str1[--i];
                } else {
                    assert(false);
                }
            } else {
                if(length == dp[i][j - 1] + 1) {
                    --length;
                    answer += str2[--j];
                } else {
                    assert(false);
                }
            }
        }

        reverse(answer.begin(), answer.end());

        return answer;
    }
};