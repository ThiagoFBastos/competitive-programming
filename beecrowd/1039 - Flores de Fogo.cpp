#include "bits/stdc++.h"

using namespace std;

struct point {
    int x;
    int y;

    double distance(const point& other) {
        return hypot(x - other.x, y - other.y);
    }
};

struct circle {
    int radius;
    point origin;
};

istream& operator>>(istream& is, point& p) {
    is >> p.x >> p.y;
    return is;
}

istream& operator>>(istream& is, circle& c) {
    is >> c.radius >> c.origin;
    return is;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    
    circle c1, c2;

    while(cin >> c1 >> c2) {
        double distance = c1.origin.distance(c2.origin);

        if(distance <= c1.radius - c2.radius) cout << "RICO\n";
        else cout << "MORTO\n";
    }

    return 0;
}
