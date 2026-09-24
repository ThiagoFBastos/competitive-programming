class Solution {
public:
    int findMin(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        const int lg = 32 - __builtin_clz(n);
        int high = n - 1;

        if(nums.front() > nums.back()) {
            for(int i = lg - 1; i >= 0; --i) {
                int low = high - (1 << i);

                if(low >= 0 && nums[low] <= nums[high])
                    high = low;
            }
        } else if(nums.front() == nums.back()) {
            high = min_element(nums.begin(), nums.end()) - nums.begin();
        } else
            high = 0;

        return nums[high];
    }
};