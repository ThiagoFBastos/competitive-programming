/**
 * @brief Segtree traits concepts with method neutral that returns the neutral
 * element and merge that returns the result of merging the results of children node
 */
template<typename Traits>
concept SegTreeInterfaceTraits = 
requires (const typename Traits::value_type& a, const typename Traits::value_type& b)
{
	typename Traits::value_type;

	{Traits::neutral()} -> std::same_as<typename Traits::value_type>;

	{Traits::merge(a, b)} -> std::same_as<typename Traits::value_type>;
}
&& std::copy_constructible<typename Traits::value_type>;

/**
 * @brief This class implements the Segment Tree data structure that can
 * solve queries and updates without using lazy operations
 */
template <SegTreeInterfaceTraits Traits>
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
	template<std::ranges::range R>
	SegTree(R&& r):
		SegTree(std::ranges::distance(r))
	{
		std::copy(std::ranges::begin(r), std::ranges::end(r), _container.begin() + _len);

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
	void update(std::size_t k, std::size_t c, int value)
	{
		if(k >= _len)
			throw std::out_of_range("index out of bounds");

		k += _len;

		_container[k][c] = static_cast<int>(_container[k][c]) ^ value;

		for(k >>= 1; k; k >>= 1)
			_container[k] = Traits::merge(_container[k << 1], _container[(k << 1) | 1]);
	}

    /**
     * @return the number of nodes
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

struct SegTreeTraits {
    using value_type = bitset<26>;

    static value_type neutral() {
        return value_type {};
    }

    static value_type merge(const value_type& lhs, const value_type& rhs) {
        return lhs ^ rhs;
    }
};

class LCA {
public:
    LCA(const vector<vector<int>>& adj) {
        const int n = (int)adj.size();
        const int lg = 32 - __builtin_clz(n);

        depth.assign(n, 0);
        sp = vector<vector<int>>(n, vector<int>(lg));

        dfs(adj, 0, 0);
    }

    int query(int u, int v) {
        if(depth[u] > depth[v])
            swap(u, v);

        int dist = depth[v] - depth[u];

        for(int i = 0; (1 << i) <= dist; ++i) {
            if(dist & (1 << i))
                v = sp[v][i];
        }

        if(u == v)
            return u;

        for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
            if(sp[u][i] == sp[v][i])
                continue;
            u = sp[u][i];
            v = sp[v][i];
        }

        return sp[u][0];
    }

private:
    vector<vector<int>> sp;
    vector<int> depth;

    void dfs(const vector<vector<int>>& adj, int u, int p) {
        const int n = (int)adj.size();

        sp[u][0] = p;
        for(int i = 1; (1 << i) <= n; ++i)
            sp[u][i] = sp[sp[u][i - 1]][i - 1];

        for(const int v : adj[u]) {
            if(v == p)
                continue;

            depth[v] = 1 + depth[u];
            dfs(adj, v, u);
        }
    }
};

class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        vector<int> low(n), high(n);
        vector<bool> answer;
        int timestamp {};

        for(const auto& edge : edges) {
            assert(edge.size() == 2);
            const int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        auto dfs = [&](auto& self, const int u, const int p) -> void {
            low[u] = timestamp++;
            
            for(const int v : adj[u]) {
                if(v == p)
                    continue;
                self(self, v, u);
            }

            high[u] = timestamp - 1;
        };

        dfs(dfs, 0, -1);

        SegTree<SegTreeTraits> st(vector<SegTreeTraits::value_type>(n, SegTreeTraits::value_type {}));
        LCA binary_lifting(adj);

        for(int i = 0; i < (int)s.size(); ++i) {
            st.update(low[i], size_t(s[i] - 'a'), 1);

            if(high[i] < n - 1)
                st.update(high[i] + 1, size_t(s[i] - 'a'), 1);
        }

        for(int i = 0; i < (int)queries.size(); ++i) {
            const auto& q = queries[i];

            istringstream is(q);
            string type;

            is >> type;

            if(type == "update") {
                int u;
                char c;
                is >> u >> c;

                st.update(low[u], s[u] - 'a', 1);

                if(high[u] < n - 1) {
                    st.update(high[u] + 1, s[u] - 'a', 1);
                    st.update(high[u] + 1, c - 'a', 1);
                }

                st.update(low[u], c - 'a', 1);
                
                s[u] = c;
            } else {
                int u, v;
                is >> u >> v;

                auto parity = SegTreeTraits::merge(st.query(0, low[u]), st.query(0, low[v]));

                const int lca = binary_lifting.query(u, v);

                const int idx = s[lca] - 'a';

                parity[idx] = static_cast<int>(parity[idx]) ^ 1;

                answer.push_back(parity.count() <= 1);
            }
        }

        return answer;
    }
};