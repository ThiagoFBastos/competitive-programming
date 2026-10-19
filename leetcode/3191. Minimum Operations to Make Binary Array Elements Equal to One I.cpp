class Solution {
public:
    int minOperations(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        int answer {};

        for(int i = 0; i <= n - 3; ++i) {
            if(nums[i] == 0) {
                nums[i] ^= 1;
                nums[i + 1] ^= 1;
                nums[i + 2] ^= 1;
                ++answer;
            }
        }

        if(!ranges::all_of(nums, std::identity()))
            return -1;

        return answer;
    }
};