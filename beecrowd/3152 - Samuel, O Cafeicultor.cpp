#include "bits/stdc++.h"

using namespace std;

struct point {
    int x;
    int y;

    int operator^(const point& other) const {
        return x * other.y - y * other.x;
    }
};

istream& operator>>(istream& is, point& p) {
    is >> p.x >> p.y;
    return is;
}

struct polygon {
    vector<point> points;

    polygon(const vector<point>& p): points(p) {}

    double area() const {
        double result = 0;
        const auto n = points.size();

        for(size_t i = 0; i < n; ++i) {
            result += points[i] ^ points[(i + 1) % n];
        }

        return abs(result) / 2.0;
    }
};

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    
    vector<point> p1(4), p2(4);
    
    for(auto& p : p1) cin >> p;
    for(auto& p : p2) cin >> p;

    polygon poly1(p1);
    polygon poly2(p2);

    if(poly1.area() > poly2.area()) cout << "terreno A\n";
    else cout << "terreno B\n";

    return 0;
}
