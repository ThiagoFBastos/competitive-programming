#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3,sse4")
#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 9;
bitset<N> g[N];
int cnt;
string path;
 
void backtracking(int k, int x, int y) {
 
	if(k == 48) {
		++cnt;
		return;
	} else if(x == 7 && y == 1) return;
	
	if(g[x-1][y]+g[x+1][y]==0&&g[x][y-1]+g[x][y+1]==2||g[x-1][y]+g[x+1][y]==2&&g[x][y-1]+g[x][y+1]==0) return;
	
	g[x][y] = 0;
	
	if(path[k] == '?') {
		if(y == 1) {
			if(g[x - 1][y]) {
				g[x][y] = 1;
				return;
			}
			
			if(g[x + 1][y]) backtracking(k + 1, x + 1, y);
			if(g[x][y + 1]) backtracking(k + 1, x, y + 1);
		} else if(y == 7) {
			if(g[x - 1][y]) {
				g[x][y] = 1;
				return;
			}	
			
			if(g[x + 1][y]) backtracking(k + 1, x + 1, y);
			if(g[x][y - 1]) backtracking(k + 1, x, y - 1);
		} else if(x == 1) {
		
			if(g[x][y - 1]) {
				g[x][y] = 1;
				return;
			}
			
			if(g[x + 1][y]) backtracking(k + 1, x + 1, y);
			if(g[x][y + 1]) backtracking(k + 1, x, y + 1);
			
		} else if(x == 7) {
			
			if(g[x][y + 1]) {
				g[x][y] = 1;
				return;
			}
			
			if(g[x][y - 1]) backtracking(k + 1, x, y - 1);
			if(g[x - 1][y]) backtracking(k + 1, x - 1, y);
				
		} else {
			if(g[x + 1][y]) backtracking(k + 1, x + 1, y);
			if(g[x][y - 1]) backtracking(k + 1, x, y - 1);
			if(g[x][y + 1]) backtracking(k + 1, x, y + 1);
			if(g[x - 1][y]) backtracking(k + 1, x - 1, y);
		}
	} else {
		if(path[k] == 'L' && g[x][y - 1]) backtracking(k + 1, x, y - 1);	
		if(path[k] == 'R' && g[x][y + 1]) backtracking(k + 1, x, y + 1);	
		if(path[k] == 'D' && g[x + 1][y]) backtracking(k + 1, x + 1, y);	
		if(path[k] == 'U' && g[x - 1][y]) backtracking(k + 1, x - 1, y);		
	}
		
	g[x][y] = 1;
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	for(int x = 0; x <= 8; ++x) g[x].set();
	for(int k = 0; k <= 8; ++k) g[0][k] = g[8][k] = g[k][0] = g[k][8] = 0;
	
	cin >> path;
	backtracking(0, 1, 1);
	
	cout<<cnt<<'\n';
		
 	return 0;
}
