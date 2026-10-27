template <typename T, typename F>
requires std::regular_invocable<F&, const T&, const T&> 
&& std::convertible_to<std::invoke_result_t<F&, const T&, const T&>, T>
&& std::copy_constructible<T>
class SparseTable
{
public:
    /**
     * @brief initialize the sparse table data structure
     * @param begin the start iterator of the sequence
     * @param end the end iterator of the sequence
     * @param op the binary function that calculates the answer
     */
    template <typename It>
	requires std::convertible_to<typename std::iterator_traits<It>::value_type, T>
    SparseTable(It begin, It end, const F& op):
        _op(op)
    {
        std::size_t n = std::distance(begin, end);

        assert(n != 0);

        std::size_t lg = 32 - __builtin_clz(n);

        _st.resize(lg);

        _st[0] = std::vector<T>(begin, end);
        
        for(std::size_t i = 1; i < lg; ++i)
            _st[i].resize(n);

        for(std::size_t i = 1; i < lg; ++i)
            for(std::size_t j = 0; j + (1 << i) <= n; ++j)
                _st[i][j] = _op(_st[i - 1][j], _st[i - 1][j + (1 << (i - 1))]);
    }

    /**
     * @brief answer the value of constant query idempotent operation
     * @param l the leftmost index of interval
     * @param r the rightmost index of interval
     */
    T query(std::size_t l, std::size_t r) const
    {
        assert(l <= r && r < _st[0].size());

        std::size_t lg = 31 - __builtin_clz(r - l + 1);

        return _op(_st[lg][l], _st[lg][r + 1 - (1 << lg)]);
    }

    /**
     * @brief answer the value of log query operation
     * @param initial the start value of the variable with the answer
     * @param l the leftmost index of interval
     * @param r the rightmost index of interval
     */
    T query(T initial, std::size_t l, std::size_t r) const
    {
       assert(l <= r && r < _st[0].size());

        auto distance = r - l + 1;
        std::size_t lg = 31 - __builtin_clz(distance);

        T answer = initial;

        for(std::size_t i = 0; i <= lg; ++i)
        {
            if(distance & (1 << i))
            {
                answer = _op(answer, _st[i][l]);
                l += (1 << i);
            }
        }

        return answer;
    }

private:
    /* the sparse table data */
    std::vector<std::vector<T>> _st;

    /* binary operator that handles with the calculation of result*/
    F _op;
};

/**
 * @brief Factory function of the sparse table data structure
 * @param begin the start iterator of the sequence
 * @param end the end iterator of the sequence
 * @param op the binary function that calculates the answer
 */
template<typename It, typename F>
inline auto make_sparse_table(It begin, It end, F&& op)
{
    using T = typename std::iterator_traits<It>::value_type;
    return SparseTable<T, std::decay_t<F>>(begin, end, std::forward<F>(op));
}

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        auto sp = make_sparse_table(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {
            return max(lhs, rhs);
        });

        const int n = static_cast<int>(arr.size());
        constexpr long long INF = 1e15L;

        vector<long long> dp(n + 1, -INF);

        dp[0] = 0;

        for(int j = 0; j < n; ++j)
            for(int len = 1; j + len <= n && len <= k; ++len)
                dp[len + j] = max(dp[len + j], dp[j] + (long long)sp.query(j, j + len - 1) * len);

        return static_cast<int>(dp.back());
    }
};