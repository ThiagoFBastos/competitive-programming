#include "bits/stdc++.h"

using namespace std;

double esphere_volume(long long radius) {
    const double PI = 3.1415;
    return pow(radius, 3) * PI * 4.0 / 3.0; 
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    
    long long radius, liter;

    cin >> radius >> liter;

    auto volume = esphere_volume(radius);

    long long cnt = liter / volume;

    cout << cnt << '\n';

    return 0;
}
