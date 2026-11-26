class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        int low = k, high = k, minimum = nums[k], answer = minimum;

        for(int i = 1; i < n; ++i) {
            if(low > 0 && high < n - 1) {
                if(nums[low - 1] > nums[high + 1])
                    minimum = min(minimum, nums[--low]);
                else
                    minimum = min(minimum, nums[++high]);
            } else if(low > 0)
                minimum = min(minimum, nums[--low]);
            else
                minimum = min(minimum, nums[++high]);

            answer = max(answer, (high - low + 1) * minimum);
        }

        return answer;
    }
};