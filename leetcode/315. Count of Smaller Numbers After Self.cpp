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
    vector<int> countSmaller(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        vector<pair<int, int>> values(n);
        vector<int> answer(n);
        auto ft = make_fenwick_tree(n, plus<int>(), 0);

        for(int i = 0; i < n; ++i)
            values[i] = {nums[i], i + 1};

        sort(values.begin(), values.end());

        for(const auto& [val, index] : values) {
            const auto pos = static_cast<size_t>(index);
            ft.update(pos, 1);
            answer[pos - 1] = ft.query(nums.size()) - ft.query(pos);
        }

        return answer;
    }
};