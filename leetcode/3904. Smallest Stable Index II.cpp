class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        constexpr int INF = numeric_limits<int>::max();

        vector<int> prefix(n + 1, -INF), suffix(n + 1, INF);

        for(int i = n - 1; i >= 0; --i)
            suffix[i] = min(suffix[i + 1], nums[i]);

        for(int i = 1; i <= n; ++i) {
            prefix[i] = max(prefix[i - 1], nums[i - 1]);

            if(prefix[i] - suffix[i - 1] <= k)
                return i - 1;
        }

        return -1;
    }
};