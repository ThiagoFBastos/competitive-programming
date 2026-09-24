class Solution {
public:
    int findMin(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        const int lg = 32 - __builtin_clz(n);
        int high = n - 1;

        for(int i = lg - 1; i >= 0; --i) {
            int low = high - (1 << i);

            if(low >= 0 && nums[low] < nums[high])
                high = low;
        }

        return nums[high];
    }
};