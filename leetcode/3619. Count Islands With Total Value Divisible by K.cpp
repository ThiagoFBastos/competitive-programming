class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());

        vector<bool> vis(n * m, false);
        constexpr pair<int, int> delta[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int answer {};

        auto index = [m](const int i, const int j) {
            return i * m + j;
        };

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(vis[index(i, j)] || !grid[i][j])
                    continue;

                long long sum {};
                queue<pair<int, int>> q;

                q.emplace(i, j);
                vis[index(i, j)] = true;

                while(!q.empty()) {
                    const auto [x, y] = q.front();
                    q.pop();

                    sum += grid[x][y];

                    for(const auto [dx, dy] : delta) {
                        int tx = x + dx, ty = y + dy;

                        if(tx < 0 || tx >= n || ty < 0 || ty >= m || !grid[tx][ty])
                            continue;
                        
                        const auto idx = index(tx, ty);

                        if(vis[idx])
                            continue;

                        vis[idx] = true;
                        q.emplace(tx, ty);
                    }
                }

                if(sum % k == 0)
                    ++answer;
            }
        }

        return answer;
    }
};