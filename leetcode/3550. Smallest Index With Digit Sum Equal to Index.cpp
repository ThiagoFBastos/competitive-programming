class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        auto digits_sum = [](int n) {
            int sum {};

            for(; n; n /= 10)
                sum += n % 10;

            return sum;
        };

        const int n = static_cast<int>(nums.size());
        int i = 0;

        while(i < n && digits_sum(nums[i]) != i)
            ++i;

        return i < n ? i : -1;
    }
};