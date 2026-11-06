struct Event {
    int time;
    int type;
    int index;

    bool operator<(const Event& rhs) const {
        if(time != rhs.time)
            return time < rhs.time;
        return type < rhs.type;
    }
};

template <typename T, typename Op>
requires std::regular_invocable<Op, T, T> && std::convertible_to<std::invoke_result_t<Op&, const T&, const T&>, T>
class FenwickTree
{
public:
    FenwickTree(std::size_t n, const Op& op, T initial):
        _ft(n + 1, initial),
        _op(op),
        _initial(initial)
    {

    }

    void update(std::size_t k, T value)
    {
        assert(k >= 1 && k < _ft.size());

        for(int i = k; i < (int)_ft.size(); i += i & -i)
            _ft[i] = _op(_ft[i], value);
    }

    T query(std::size_t k) const
    {
        T answer = _initial;

        assert(k < _ft.size());

        for(int i = k; i > 0; i -= i & -i)
            answer = _op(answer, _ft[i]);

        return answer;
    }
private:
    std::vector<T> _ft;

    Op _op;

    T _initial;
};

template<typename T, typename Op>
auto make_fenwick_tree(std::size_t n, Op&& op, T initial)
{
    return FenwickTree<T, std::decay_t<Op>>(n, std::forward<Op>(op), initial);
}

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        const int m = static_cast<int>(logs.size());
        const int q = static_cast<int>(queries.size());
        vector<int> answer(q, 0), times(m), previous(n + 1, -1);
        vector<Event> sweep;

        sweep.reserve(m + q);

        sort(logs.begin(), logs.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[1] < rhs[1];
        });

        for(int i = 0; i < m; ++i) {
            const auto& log = logs[i];
            assert(log.size() == 2);
            sweep.push_back({log[1], 0, i});
            times[i] = log[1];
        }

        for(int i = 0; i < q; ++i)
            sweep.push_back({queries[i], 1, i});

        sort(sweep.begin(), sweep.end());

        auto servers_index = make_fenwick_tree(m, plus<int>(), 0);;

        for(const auto& [t, type, index] : sweep) {
            if(type == 0) {
                const int id = logs[index][0];

                if(previous[id] != -1)
                    servers_index.update(previous[id] + 1, -1);

                servers_index.update(index + 1, 1);
                previous[id] = index;
            } else {
                int low = lower_bound(times.begin(), times.end(), t - x) - times.begin();
                int high = upper_bound(times.begin(), times.end(), t) - times.begin();

                const int inside = servers_index.query(high) - servers_index.query(low);

                answer[index] = n - inside;
            }
        }
        
        return answer;
    }
};