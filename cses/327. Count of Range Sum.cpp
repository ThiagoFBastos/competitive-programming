template <typename T, typename Op>
requires std::regular_invocable<Op, T, T> && std::convertible_to<std::invoke_result_t<Op&, const T&, const T&>, T>
class FenwickTree
{
public:
    /**
     * @brief Initialize the fenwick tree data structure
     * @param n the number of elements
     * @param op the binary operator that calculates the result
     * @param initial the default value that will be used when there is not value
     */
    FenwickTree(std::size_t n, const Op& op, T initial):
        _ft(n + 1, initial),
        _op(op),
        _initial(initial)
    {

    }

    /**
     * @brief Update the fenwick tree data structure
     * @param k the index of a element in the fenwick data structure
     * @param value the value that will be applied to the element
     */
    void update(std::size_t k, T value)
    {
        assert(k >= 1 && k < _ft.size());

        for(int i = k; i < (int)_ft.size(); i += i & -i)
            _ft[i] = _op(_ft[i], value);
    }

    /**
     * @brief Find the result of an operation of first k elements
     * @param k the number of the first elements for which we want to find the result
     */
    T query(std::size_t k) const
    {
        T answer = _initial;

        assert(k < _ft.size());

        for(int i = k; i > 0; i -= i & -i)
            answer = _op(answer, _ft[i]);

        return answer;
    }
private:
    /* The fenwick tree data structure */
    std::vector<T> _ft;

    /* The binary operator that calculates the answer */
    Op _op;

    /* The default value that is used when there is not a value to assign */
    T _initial;
};

/**
  * @brief Factory of the FenwickTree
  * @param n the number of elements
  * @param op the binary operator that calculates the result
  * @param initial the default value that will be used when there is not value
  * @return The FenwickTree data structure
 */
template<typename T, typename Op>
auto make_fenwick_tree(std::size_t n, Op&& op, T initial)
{
    return FenwickTree<T, std::decay_t<Op>>(n, std::forward<Op>(op), initial);
}

class OrderedSet {
public:
    OrderedSet(const vector<long long>& keys)
    : _keys(keys)
    , _ft(make_fenwick_tree(keys.size(), plus<int>(), 0))
    , _count(0)
    {
        sort(_keys.begin(), _keys.end());
    }

    void insert(long long key) {
        auto it = lower_bound(_keys.begin(), _keys.end(), key);
        assert(it != _keys.end());
        size_t k = distance(_keys.begin(), it);
        _ft.update(k + 1, 1);
        ++_count;
    }

    int order_of_key(long long key) const {
        auto it = lower_bound(_keys.begin(), _keys.end(), key);
        size_t k = distance(_keys.begin(), it);
        return _ft.query(k);
    }

    size_t size() const {
        return _count;
    }

private:
    vector<long long> _keys;
    FenwickTree<int, decltype(plus<int>())> _ft;
    size_t _count;
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        const int n = static_cast<int>(nums.size());
        vector<long long> prefix(n + 1, 0);

        for(int i = 1; i <= n; ++i)
            prefix[i] = prefix[i - 1] + nums[i - 1];

        auto count_until_sum = [&](int upper) {
            OrderedSet st(prefix);
            long long cnt {};

            st.insert(0ll);

            for(int i = 1; i <= n; ++i) {
                const auto target = prefix[i] - upper;
                cnt += static_cast<int>(st.size()) - st.order_of_key(target);
                st.insert(prefix[i]);
            }

            return cnt;
        };

        const int cnt = static_cast<int>(count_until_sum(upper) - count_until_sum(lower - 1));

        return cnt;
    }
};