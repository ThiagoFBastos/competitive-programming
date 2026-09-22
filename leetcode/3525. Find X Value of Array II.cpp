class SegTree {
public:
    static constexpr int K = 5;
    using value_type = array<int, K>;

    SegTree(const vector<int>& nums, int mod)
        : _mod(mod)
        , _length(nums.size())
    {
        const auto n = nums.size();

        _st.resize(2 * n);
        _moduloAll.resize(2 * n);

        for(size_t i = n; i < 2 * n; ++i) {
            int val = nums[i - n] % mod;
            _st[i].fill(0);
            _st[i][val] = 1;
            _moduloAll[i] = val;
        }

        for(size_t i = n - 1; i > 0; --i)
            _st[i] = merge(_moduloAll[i], _st[i << 1], _moduloAll[i << 1], _st[(i << 1) | 1], _moduloAll[(i << 1) | 1]);
    }

    void update(size_t k, int x) {
        k += _length;

        x %= _mod;
        _st[k].fill(0);
        _st[k][x] = 1;
        _moduloAll[k] = x;

        for(k >>= 1; k > 0; k >>= 1)
             _st[k] = merge(_moduloAll[k], _st[k << 1], _moduloAll[k << 1], _st[(k << 1) | 1], _moduloAll[(k << 1) | 1]);
    }

    int query(int l, int r, int x) {
        value_type answer_left {}, answer_right {};
        int mod_left = 1, mod_right = 1;

        x %= _mod;
        l += _length;
        r += _length;

        while(l <= r) {

            if(l & 1) {
                answer_left = merge(mod_left, answer_left, mod_left, _st[l], _moduloAll[l]);
                ++l;
            }

            if(~r & 1) {
                answer_right = merge(mod_right, _st[r], _moduloAll[r], answer_right, mod_right);
                --r;
            }

            l >>= 1;
            r >>= 1;
        }

        int moduloAll = 1;

        auto answer = merge(moduloAll, answer_left, mod_left, answer_right, mod_right);

        return answer[x];
    }

private:
    vector<value_type> _st;
    vector<int> _moduloAll;
    size_t _length;
    int _mod;

    inline value_type merge(int& mod_dest, const value_type& lhs, int mod_lhs, const value_type& rhs, int mod_rhs) {
        value_type dest = lhs;

        for(int i = 0; i < _mod; ++i)
            dest[mod_lhs * i % _mod] += rhs[i];

        mod_dest = mod_lhs * mod_rhs % _mod;

        return dest;
    }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        SegTree st(nums, k);
        vector<int> answer(queries.size());
        const int n = static_cast<int>(nums.size());

        for(size_t i = 0; i < queries.size(); ++i) {
            auto& data = queries[i];
            int index = data[0], value = data[1], start = data[2], x = data[3];

            st.update(index, value);

            answer[i] = st.query(start, n - 1, x);
        }

        return answer;
    }
 };