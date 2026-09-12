#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

class Solution {
public:
    long long countRatioSubarrays(vector<int>& nums, int a, int b) {
       /* 
        (pre0(r) - pre0(l)) / (pre1(r) - pre1(l)) <= a / b

        (pre0(r) - pre0(l)) * b <= (pre1(r) - pre1(l)) * a

        pre0(r) * b - pre1(r) * a <= pre0(l) * b - pre1(l) * a
      */

        const int n = static_cast<int>(nums.size());
        int odd = 0, even = 0;
        ordered_set<pair<long long, int>> st;
        long long cnt = 0;

        st.insert(make_pair(0, 0));

        for(int i = 0; i < n; ++i) {
            odd += nums[i] % 2;
            even += (1 + nums[i]) % 2;

            cnt += st.size() - st.order_of_key(make_pair(1ll * even * b - 1ll * odd * a, -1));

            st.insert(make_pair(1ll * even * b - 1ll * odd * a, i + 1));
        }

        return cnt;
    }
};