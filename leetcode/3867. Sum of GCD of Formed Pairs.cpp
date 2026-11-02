class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        vector<int> prefixMAX(n), prefixGCD(n);

        partial_sum(nums.begin(), nums.end(), prefixMAX.begin(), ranges::max);

        for(int i = 0; i < n; ++i)
            prefixGCD[i] = gcd(nums[i], prefixMAX[i]);

        ranges::sort(prefixGCD);

        long long answer {};

        for(int low = 0, high = n - 1; low < high; ++low, --high)
            answer += gcd(prefixGCD[low], prefixGCD[high]);

        return answer;
    }
};