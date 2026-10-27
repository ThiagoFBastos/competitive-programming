class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());
        vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
        int answer {};

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                prefix[i][j] = prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1] + grid[i - 1][j - 1];
                answer += prefix[i][j] <= k;
            }
        }

        return answer;
    }
};