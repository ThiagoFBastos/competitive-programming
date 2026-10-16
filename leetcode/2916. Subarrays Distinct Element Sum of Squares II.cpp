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

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        constexpr int N = 1e5 + 5;
        vector<int> pos(N, 0), last(N, -1);
        const int n = static_cast<int>(nums.size());
        int sum_pairs {}, sum_positions {};
        constexpr int MOD = 1e9 + 7;
        vector<int> nxt(n);

        auto ft = make_fenwick_tree(n, [](const auto& lhs, const auto& rhs) {
            return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
        }, make_pair(0ll, 0));

        for(int i = n - 1; i >= 0; --i) {
            const int val = nums[i];
            nxt[i] = last[val] != -1 ? last[val] : n;
            last[val] = i;
        }

        fill(last.begin(), last.end(), -1);

        for(int i = 0; i < n; ++i) {
            const int val = nums[i];
            
            sum_positions = (sum_positions - pos[val] + MOD) % MOD;

            pos[val] = i + 1;

            if(last[val] != -1) {
                const int pos = last[val] - 1;
                ft.update(pos + 1, make_pair<long long, int>(-nxt[pos], -1));
            }

            int cnt = ((i + 1ll) * (nxt[i] - i) + (long long)sum_positions * (nxt[i] - i) * 2) % MOD;

            if(last[val] != -1) {
                const int pos = last[val];
                const auto [sumR, frequencyR] = ft.query(i);
                const auto [sumL, frequencyL] = ft.query(pos);
                
                int frequency = frequencyR - frequencyL;
                long long ending =  sumR - sumL;
                long long between = 2 * (ending - (long long)i * frequency); 

                cnt = (cnt - between % MOD * pos) % MOD;
            }
            
            sum_pairs = (sum_pairs + cnt) % MOD;
            sum_positions = (sum_positions + i + 1) % MOD;

            ft.update(i + 1, make_pair<long long, int>(nxt[i], 1));
            last[val] = i + 1;
        }

        return (sum_pairs + MOD) % MOD;
    }
};