#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    
    size_t w, h;

    while(cin >> w >> h) {
        vector<string> grid(h);
        int x0 {-1}, y0 {-1}, gold {};
        pair<int, int> delta[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        for(size_t i = 0; i < h; ++i) {
            cin >> grid[i];
            for(size_t j = 0; j < w && x0 < 0; ++j) {
                if(grid[i][j] == 'P') {
                    x0 = i, y0 = j;
                    break;
                }
            }
        }

        function<void(int, int)> dfs = [&](int x, int y) {
            assert(x >= 0 && x < h && y0 >= 0 && y0 < w);

            if(grid[x][y] == 'G')
                ++gold;

            grid[x][y] = '#';

            bool traps {};

            for(auto& d : delta) {
                int xto = x + d.first;
                int yto = y + d.second;

                traps = traps || grid[xto][yto] == 'T';
            }

            if(traps) return;

            for(auto& d : delta) {
                int xto = x + d.first;
                int yto = y + d.second;

                if(grid[xto][yto] != '#' && grid[xto][yto] != 'T')
                    dfs(xto, yto);
            }
        };

        dfs(x0, y0);

        cout << gold << '\n';
    }

    return 0;
}