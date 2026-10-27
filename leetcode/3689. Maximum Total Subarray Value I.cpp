class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        const auto [min, max] = minmax_element(nums.begin(), nums.end());
        return (long long)(*max - *min) * k;
    }
};