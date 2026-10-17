class Solution {
public:
    int minSwaps(vector<int>& nums) {
        auto sum_digits = [](int x) {
            int sum {};
            for(; x > 0; x /= 10)
                sum += x % 10;
            return sum;
        };

        auto values = nums | views::transform([sum_digits](const int val) {
            return make_pair(sum_digits(val), val);
        }) | ranges::to<vector<pair<int, int>>>();

        auto sorted_values = values;

        sort(sorted_values.begin(), sorted_values.end());

        const int n = static_cast<int>(values.size());
        vector<int> permutation(n);
        vector<bool> vis(n, false);
        int swaps {};

        for(int i = 0; i < n; ++i) {
            auto it = lower_bound(sorted_values.begin(), sorted_values.end(), values[i]);
            permutation[i] = distance(sorted_values.begin(), it);
        }

        for(int i = 0; i < n; ++i) {
            if(vis[i])
                continue;
            
            int cycle_size {};

            for(int j = i; !vis[j]; j = permutation[j]) {
                vis[j] = true;
                ++cycle_size;
            }

            swaps += cycle_size - 1;
        }

        return swaps;
    }
};