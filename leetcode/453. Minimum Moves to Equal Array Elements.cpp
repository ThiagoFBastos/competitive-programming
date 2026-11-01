class Solution {
public:
    int minMoves(vector<int>& nums) {
        const int min_value = *min_element(nums.begin(), nums.end());
        int answer {};

        for(const int val : nums)
            answer += val - min_value;

        return answer;
    }
};