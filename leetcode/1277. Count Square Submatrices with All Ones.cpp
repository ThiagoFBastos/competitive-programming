class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        const int n = static_cast<int>(matrix.size());
        const int m = static_cast<int>(matrix[0].size());
        int answer {};

        vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));

        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + matrix[i - 1][j - 1];

        auto query = [&prefix](const int x0, const int y0, const int x1, const int y1) {
            return prefix[x1][y1] - prefix[x1][y0 - 1] - prefix[x0 - 1][y1] + prefix[x0 - 1][y0 - 1];
        };

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(matrix[i - 1][j - 1] == 0)
                    continue;

                int low = 1, high = min(i, j) + 1;

                while(low < high) {
                    int mid = (low + high) / 2;

                    if(query(i - mid + 1, j - mid + 1, i, j) != mid * mid)
                        high = mid;
                    else
                        low = mid + 1;
                }

                answer += high - 1;
            }
        }

        return answer;
    }
};