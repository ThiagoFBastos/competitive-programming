class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        const int n = static_cast<int>(nums.size());
        using element_type = pair<int, int>;
        
        constexpr int INF = 1e9;
        vector<element_type> elements;
        vector<int> frq(n, 0);
        int cnt {}, low = 0, lo = -INF, hi = INF;

        for(int i = 0; i < n; ++i) {
            auto values = nums[i] | views::transform([i](int val) {
                return make_pair(val, i);
            }) | ranges::to<vector<element_type>>();

            const size_t m = elements.size();
            
            elements.insert(elements.end(), values.begin(), values.end());
        }

        sort(elements.begin(), elements.end());

        for(int i = 0; i < (int)elements.size(); ++i) {
            const auto [value, idx] = elements[i];

            if(frq[idx]++ == 0)
                ++cnt;

            while(low < i && frq[elements[low].second] > 1)
                --frq[elements[low++].second];

            if(cnt == n) {
                int l = elements[low].first, r = value;

                if(r - l < hi - lo)
                    lo = l, hi = r;
            }
        }

        return {lo, hi};
    }
};