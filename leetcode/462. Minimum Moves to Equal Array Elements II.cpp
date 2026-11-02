class Solution {
public:
    int minMoves2(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        long long sumRight = ranges::fold_left(nums, 0ll, plus<>());
        long long sumLeft {}, answer = numeric_limits<long long>::max();

        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < n; ++i) {
            const long long moves = (long long)i * nums[i] - sumLeft + sumRight - (long long)(n - i) * nums[i];
            answer = min(answer, moves);
            sumLeft += nums[i];
            sumRight -= nums[i];
        }

        return static_cast<int>(answer);
    }
};