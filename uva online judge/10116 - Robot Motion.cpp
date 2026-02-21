#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int n, m, c;

    unordered_map<char, pair<int, int>> delta = {
        {'N', {-1, 0}},
        {'S', {1, 0}},
        {'W', {0, -1}},
        {'E', {0, 1}}
    };

    while(cin >> n >> m >> c && n + m + c != 0) {
        vector<string> grid(n);

        for(auto& r : grid) cin >> r;

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        vector<pair<int, int>> path;

        int x = 0, y = c - 1;

        while(x >= 0 && x < n && y >= 0 && y < m && !vis[x][y]) {
            vis[x][y] = true;
            path.emplace_back(x, y);
            
            int dx, dy;
            tie(dx, dy) = delta[grid[x][y]];

            x += dx;
            y += dy;            
        }

        if(x < 0 || x >= n || y < 0 || y >= m) {
            cout << path.size() << " step(s) to exit\n";
            continue;
        }

        int cycle {1};

        while(path.back() != make_pair(x, y)) {
            ++cycle;
            path.pop_back();
        }

        path.pop_back();
        
        cout << path.size() << " step(s) before a loop of " << cycle << " step(s)\n";
    }

    return 0;
}