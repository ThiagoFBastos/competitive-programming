#include <bits/stdc++.h>

using namespace std;

class Traits
{
public:

    using value_type = int;

    static constexpr value_type neutral()
    {
        return numeric_limits<value_type>::max();
    }

    static value_type merge(value_type left, value_type right)
    {
        return min(left, right);
    }
};

/**
 * @brief This class implements the Segment Tree data structure that can
 * solve queries and updates without using lazy operations
 */
template <typename Traits>
class SegTree
{
public:

	using value_type = typename Traits::value_type;

    /**
     * @brief Initialize the Segment Tree data structure with neutral elements
     * @param n the number of nodes
     */
	SegTree(std::size_t n):
		_len(n)
	{
		if(n == 0)
			throw std::invalid_argument("the size must be greater than zero");

		_container.assign(2 * n, Traits::neutral());
	}

    /**
     * @brief Initialize the Segment Tree data structure with the values
     * of range R
     * @param R the range of values 
     */
	template<typename R>
	SegTree(R&& r):
		SegTree((std::size_t)std::distance(r.begin(), r.end()))
	{
		std::copy(std::begin(r), std::end(r), _container.begin() + _len);

		for(size_t i = _len - 1; i > 0; --i)
			_container[i] = Traits::merge(_container[i << 1], _container[(i << 1) | 1]);
	}

    /**
     * @brief Calculate the result of merging all reacheable nodes using the merge method
     * from the trait
     * @param l the leftmost position in the segment
     * @param r the rightmost position in the segment
     */
	value_type query(std::size_t l, std::size_t r) const
	{
		value_type result_left = Traits::neutral();
		value_type result_right = Traits::neutral();

		if(l > r)
			throw std::invalid_argument("the range is degenerated");
		else if(r >= _len)
			throw std::out_of_range("range out of bounds");

		for(l += _len, r += _len; l <= r; l >>= 1, r >>= 1)
		{
			if(l & 1) result_left = Traits::merge(result_left, _container[l++]);
			if(~r & 1) result_right = Traits::merge(_container[r--], result_right);
		}

		return Traits::merge(result_left, result_right);
	}

    /**
     * @brief Update the target position to receive the new value
     * @param k the position of the element
     * @param value the new value
     */
	void update(std::size_t k, value_type value)
	{
		if(k >= _len)
			throw std::out_of_range("index out of bounds");

		k += _len;

		_container[k] = value;

		for(k >>= 1; k; k >>= 1)
			_container[k] = Traits::merge(_container[k << 1], _container[(k << 1) | 1]);
	}

    /**
     * @return Return the number of nodes
     */
	std::size_t size() const noexcept
	{
		return _len;
	}

private:

    /** The number of nodes */
	std::size_t _len;

    /** The container of nodes */
	std::vector<value_type> _container;
};

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int n, q;

    cin >> n >> q;

    vector<int> a(n);

    for(int& v : a) cin >> v;

    SegTree<Traits> st(a);
    
    while(q-- > 0) {
        string cmd;

        cin >> cmd;

        replace_if(cmd.begin(), cmd.end(), [](char c) {
            return c == '(' || c == ')' || c == ',';
        }, ' ');

        stringstream ss(cmd);
        string query;

        ss >> query;

        if(query == "query") {
            size_t l, r;

            ss >> l >> r;

            cout << st.query(l - 1, r - 1) << '\n';
        } else {
            vector<size_t> index(istream_iterator<size_t>(ss), istream_iterator<size_t>{});
            vector<size_t> shifted(index.size());

            for(size_t i = 0; i < index.size(); ++i) {
                --index[i];
                shifted[(i + index.size() - 1) % index.size()] = a[index[i]];
            }

            for(size_t i = 0; i < index.size(); ++i) {
                a[index[i]] = shifted[i];
                st.update(index[i], a[index[i]]);
            }
        }
    }

    return 0;
}
