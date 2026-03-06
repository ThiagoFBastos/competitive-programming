#include "bits/stdc++.h"

using namespace std;

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    
    int n, h, c, l;

    while(cin >> n >> h >> c >> l) {
        double diagonal = hypot(h * n, c * n) * l;
        cout << fixed << setprecision(4) << diagonal / 1e4 << '\n';
    }

    return 0;
}
