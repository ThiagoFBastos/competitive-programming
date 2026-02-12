#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
};

point rotate(const point& p, double theta, point origin = {0, 0}) {
    double x = origin.x + (p.x - origin.x) * cos(theta) - (p.y - origin.y) * sin(theta);
    double y = origin.y + (p.x - origin.x) * sin(theta) + (p.y - origin.y) * cos(theta);
    return {x, y};
}

struct line {
    double a, b, c;
};

line circle_equation(const point& p1, const point& p2) {
    line l;

    l.a = -2 * p1.x + 2 * p2.x;
    l.b = -2 * p1.y + 2 * p2.y;
    l.c = pow(p2.x, 2) + pow(p2.y, 2) - pow(p1.x, 2) - pow(p1.y, 2);

    return l;
}

point solve_equation(const line& e1, const line& e2) {
    double det = e1.a * e2.b - e1.b * e2.a;
    double detx = e1.c * e2.b - e1.b * e2.c;
    double dety = e1.a * e2.c - e1.c * e2.a;

    return {detx / det, dety / det};
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int tc = 1;

    while(true) {
        int n;
        point p1, p2, p3;

        cin >> n;

        if(!n) break;

        cin >> p1.x >> p1.y;
        cin >> p2.x >> p2.y;
        cin >> p3.x >> p3.y;

        line l1 = circle_equation(p1, p2);
        line l2 = circle_equation(p1, p3);

        auto c = solve_equation(l1, l2);

        double xmin = numeric_limits<double>::max();
        double xmax = numeric_limits<double>::lowest();
        double ymin = numeric_limits<double>::max();
        double ymax = numeric_limits<double>::lowest();
        
        double angle = 2.0 * acos(-1) / n;
        
        for(int i = 0; i < n; ++i) {
            auto p = rotate(p1, i * angle, c);

            xmin = min(xmin, p.x);
            xmax = max(xmax, p.x);
            ymin = min(ymin, p.y);
            ymax = max(ymax, p.y);
        }

        cout.precision(3);
        cout.setf(ios_base::fixed);

        cout << "Polygon " << tc++ << ": " << (xmax - xmin) * (ymax - ymin) << '\n';
    }

    return 0;
}
