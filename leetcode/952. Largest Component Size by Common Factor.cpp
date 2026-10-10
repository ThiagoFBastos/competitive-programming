class DisjointSet {
public:
    DisjointSet(int n)
        : _parent(n)
        , _rank(n, 0)
        , _size(n, 0)
    {
        iota(_parent.begin(), _parent.end(), 0);
    }

    size_t find_set(size_t p) noexcept {
        return p == _parent[p] ? p : _parent[p] = find_set(_parent[p]);
    }

    void join(size_t u, size_t v) noexcept {
        u = find_set(u);
        v = find_set(v);

        if(u == v) return;
        else if(_rank[u] > _rank[v]) swap(u, v);

        _parent[u] = v;
        _size[v] += _size[u];
        _rank[v] += _rank[v] + unsigned(_rank[u] == _rank[v]);
    }

    void set_size(size_t k) {
        _size[k] = 1;
    }

    unsigned get_size(size_t k) {
        return _size[find_set(k)];
    }

private:
    vector<size_t> _parent;
    vector<unsigned> _rank, _size;
};

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        const int n = *max_element(nums.begin(), nums.end());
        constexpr int N = 1e5 + 5;
        bitset<N> is_prime, belong_to_set;
        DisjointSet uf(n + 1);

        is_prime.set();

        for(const int val : nums) {
            uf.set_size(val);
            belong_to_set[val] = 1;
        }

        for(int p = 2; p <= n; ++p) {
            if(!is_prime[p])
                continue;

            for(int i = 2 * p; i <= n; i += p) {
                is_prime[i] = 0;

                if(belong_to_set[i])
                    uf.join(p, i);
            }
        }

        int max_connected_component {};

        for(const int val : nums)
            max_connected_component = max<int>(max_connected_component, uf.get_size(static_cast<size_t>(val)));

        return max_connected_component;
    }
};