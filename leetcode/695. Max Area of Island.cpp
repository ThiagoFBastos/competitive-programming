class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());
        constexpr pair<int, int> delta[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int answer {};

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(vis[i][j] || !grid[i][j])
                    continue;

                queue<pair<int, int>> q;
                int vertices {};

                q.emplace(i, j);
                vis[i][j] = true;

                while(!q.empty()) {
                    const auto [x, y] = q.front();
                    q.pop();
                    ++vertices;

                    for(const auto [dx, dy] : delta) {
                        int tx = x + dx, ty = y + dy;

                        if(tx < 0 || ty < 0 || tx >= n || ty >= m || !grid[tx][ty] || vis[tx][ty])
                            continue;

                        vis[tx][ty] = true;
                        q.emplace(tx, ty);
                    }
                }

                answer = max(answer, vertices);
            }
        }

        return answer;
    }
};