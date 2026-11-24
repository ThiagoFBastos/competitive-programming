class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        constexpr int MOD = 1e9 + 7;
        int dp[2] = {1, 0}, sum {}, cnt {};

        for(const int val : arr) {
            sum = (sum + val) % 2;
            cnt = (cnt + dp[sum ^ 1]) % MOD;
            ++dp[sum];
        }

        return cnt;
    }
};