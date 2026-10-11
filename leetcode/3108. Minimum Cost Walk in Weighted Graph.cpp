class DisjointSet {
public:
    DisjointSet(int n)
    : _parent(n)
    , _bitwise_and(n, -1)
    , _rank(n, 0)
    {
        iota(_parent.begin(), _parent.end(), 0);
    }

    int find_set(const int u) noexcept {
        return u == _parent[u] ? u : _parent[u] = find_set(_parent[u]);
    }

    bool same(const int u, const int v) noexcept {
        return find_set(u) == find_set(v);
    }

    void join(int u, int v, int w) noexcept {
        u = find_set(u);
        v = find_set(v);

        if(u == v)
            return;
        else if(_rank[u] > _rank[v])
            swap(u, v);

        _parent[u] = v;
        _bitwise_and[v] &= _bitwise_and[u] & w;
        _rank[v] += static_cast<unsigned>(_rank[u] == _rank[v]);
    }

    void add_edge(const int u, const int v, const int w) {
        if(same(u, v))
            _bitwise_and[find_set(u)] &= w;
        else
            join(u, v, w);
    }

    int get_bitwise_and(int u) {
        return _bitwise_and[find_set(u)];
    }
private:
    vector<int> _parent, _bitwise_and;
    vector<unsigned> _rank;
};

class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        DisjointSet uf(n);
        vector<int> answer(query.size());

        for(const auto& edge : edges) {
            assert(edge.size() == 3);
            const int u = edge[0], v = edge[1], w = edge[2];
            uf.add_edge(u, v, w);
        }

        for(size_t i = 0; i < query.size(); ++i) {
            const auto& q = query[i];
            assert(q.size() == 2);
            const int u = q[0], v = q[1];

            if(uf.same(u, v))
                answer[i] = uf.get_bitwise_and(u);
            else
                answer[i] = -1;
        }

        return answer;
    }
};