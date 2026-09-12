#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e3 + 5;

int timestamp[N][N], timevis[N][N];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	pair<int, int> delta[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	cin >> t;

	while(t-- > 0) {
		int n, m;

		cin >> n >> m;

		vector<string> grid(n);
		optional<pair<int, int>> starting, ending;

		for(int i = 0; i < n; ++i) {
			cin >> grid[i];

			for(int j = 0; j < m; ++j) {
				timestamp[i][j] = timevis[i][j] = -1;

				if(grid[i][j] == 'S')
					starting = make_pair(i, j);
				else if(grid[i][j] == 'E')
					ending = make_pair(i, j);
			}
		}

		assert(starting);

		queue<pair<int, int>> q;

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(grid[i][j] == 'F') {
					timestamp[i][j] = 0;
					q.emplace(i, j);
				}
			}
		}

		while(!q.empty()) {
			auto [x, y] = q.front();
			q.pop();

			for(auto [dx, dy] : delta) {
				int dest_x = x + dx, dest_y = y + dy;

				if(dest_x < 0 || dest_y < 0 || dest_x >= n || dest_y >= m || timestamp[dest_x][dest_y] != -1 || grid[dest_x][dest_y] == '#')
					continue;

				timestamp[dest_x][dest_y] = timestamp[x][y] + 1;
				q.emplace(dest_x, dest_y);
			}
		}

		auto [x0, y0] = *starting;

		timevis[x0][y0] = 0;
		q.emplace(x0, y0);

		while(!q.empty()) {
			auto [x, y] = q.front();
			q.pop();

			if(make_optional<pair<int, int>>(x, y) == ending)
				break;

			for(auto [dx, dy] : delta) {
				int dest_x = x + dx, dest_y = y + dy;

				if(dest_x < 0 || dest_y < 0 || dest_x >= n || dest_y >= m || timevis[dest_x][dest_y] != -1 || timestamp[dest_x][dest_y] <= timevis[x][y] + 1 || grid[dest_x][dest_y] == '#')
					continue;

				timevis[dest_x][dest_y] = timevis[x][y] + 1;
				q.emplace(dest_x, dest_y);
			}
		}

		if(!ending) cout << "N\n";
		else {
			auto [xf, yf] = *ending;
			cout << (timevis[xf][yf] != -1 ? "Y\n" : "N\n");
		}
	}

	return 0;
}