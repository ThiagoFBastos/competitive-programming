class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        const int n = static_cast<int>(grid.size());
        const int m = static_cast<int>(grid[0].size());
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        constexpr pair<int, int> delta[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int islands {};

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(vis[i][j] || grid[i][j] != 0)
                    continue;

                queue<pair<int, int>> q;
                bool is_island = true;

                q.emplace(i, j);

                while(!q.empty()) {
                    const auto [x, y] = q.front();
                    q.pop();

                    for(const auto [dx, dy] : delta) {
                        int target_x = x + dx, target_y = y + dy;

                        is_island = is_island && target_x >= 0 && target_x < n && target_y >= 0 && target_y < m;

                        if(target_x < 0 || target_x >= n || target_y < 0 || target_y >= m || grid[target_x][target_y] == 1 || vis[target_x][target_y])
                            continue;

                        vis[target_x][target_y] = true;
                        q.emplace(target_x, target_y);
                    }
                }

                if(is_island)
                    ++islands;
            }
        }

        return islands;
    }
};