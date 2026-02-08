#include <bits/stdc++.h>

using namespace std;

struct point {
	double x, y;

	double distance(const point& rhs) {
		return hypot(x - rhs.x, y - rhs.y);
	}
};

struct equation {
	double a, b, c;
};

equation circle_equation(const point& p1, const point& p2) {
	equation e;

	e.a = -2 * p1.x + 2 * p2.x;
	e.b = -2 * p1.y + 2 * p2.y;
	e.c = pow(p2.x, 2) + pow(p2.y, 2) - pow(p1.x, 2) - pow(p1.y, 2);

	return e;
}

point solve_equation(const equation& e1, const equation& e2) {
	double det = e1.a * e2.b - e1.b * e2.a;
	double detx = e1.c * e2.b - e1.b * e2.c;
	double dety = e1.a * e2.c - e1.c * e2.a;

	return {detx / det, dety / det};
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	point p1, p2, p3;

	constexpr double PI = 3.141592653589793;

	while(cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y) {
		auto e1 = circle_equation(p1, p2);
		auto e2 = circle_equation(p1, p3);

		auto p = solve_equation(e1, e2);

		double r = p1.distance(p);

		cout << fixed << setprecision(2) << 2.0 * PI * r << '\n';
	}
	
	return 0;
} 
