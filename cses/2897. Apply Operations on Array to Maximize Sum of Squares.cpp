class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        constexpr int MOD = 1e9 + 7;
        constexpr int BITS = 31;
        int sum_squares = 0;
        const int n = static_cast<int>(nums.size());
        array<int, BITS> bits {};

        for(const int val : nums)
            for(int i = 0; i < BITS; ++i)
                bits[i] += (val >> i) & 1;

        for(int i = 0; i < k; ++i) {
            for(int j = 0; j < BITS; ++j) {
                if(bits[j] > 0) {
                    nums[i] |= 1 << j;
                    --bits[j];
                } else
                    nums[i] &= ~(1 << j);
            }

            sum_squares = (sum_squares + 1ll * nums[i] * nums[i] % MOD) % MOD;
        }

        return sum_squares;
    }
};