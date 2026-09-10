#include <bits/stdc++.h>

using namespace std;

template<class T>
class BIT2D 
{
public:

	BIT2D(size_t rows, size_t columns): 
		_data (rows + 1, vector<T>(columns + 1, 0)),
		_rows (rows),
		_columns (columns)
	{
		
	}

	void update(size_t x, size_t y, T value)
	{
		assert(x && y);

		for(; x <= _rows; x += x & (~x + 1))
			for(size_t k = y; k <= _columns; k += k & (~k + 1))
				_data[x][k] += value;
	}

	T query(size_t x, size_t y)
	{
		T answer {};

		for(; x > 0; x -= x & (~x + 1))
			for(size_t k = y; k > 0; k -= k & (~k + 1))
				answer += _data[x][k];

		return answer;
	}

	T query(size_t x0, size_t y0, size_t x1, size_t y1)
	{
		return query(x1, y1) - query(x1, y0 - 1) - query(x0 - 1, y1) + query(x0 - 1, y0 - 1);
	}	

private:
	vector<vector<T>> _data;
	size_t _rows;
	size_t _columns;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	constexpr int N = 5e2;
	BIT2D<int> bit(N, N);
	size_t q;

	cin >> q;

	for(size_t i = 0; i < q; ++i) {
		char cmd;

		cin >> cmd;

		if(cmd == 'U') {
			size_t x0, y0, x1, y1;
			int val;

			cin >> x0 >> y0 >> x1 >> y1 >> val;

			bit.update(x0, y0, val);
			bit.update(x1 + 1, y0, -val);
			bit.update(x0, y1 + 1, -val);
			bit.update(x1 + 1, y1 + 1, val);
		} else {
			size_t x, y;

			cin >> x >> y;

			cout << bit.query(1, 1, x, y) << '\n';
		}
	}

	return 0;
}