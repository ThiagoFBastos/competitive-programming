class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());
        vector<int> rows(n, 0);
        int answer {};

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                rows[i] <<= 1;
                rows[i] += grid[i][j];
            }
        } 

        for(int mask = 0; mask < (1 << m); ++mask) {
            int sum {};

            for(const int val : rows) {
                int current = val ^ mask;
                sum += max(current, current ^ ((1 << m) - 1));
            }

            answer = max(answer, sum);
        }

        return answer;
    }  
};