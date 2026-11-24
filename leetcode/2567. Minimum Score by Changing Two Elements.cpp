class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());

        sort(nums.begin(), nums.end());

        int answer = nums[n - 2] - nums[1];

        answer = min(answer, nums[n - 3] - nums[0]);
        answer = min(answer, nums[n - 1] - nums[2]);

        return answer;
    }
};