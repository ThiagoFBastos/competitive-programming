class Solution {
public:
    int maxProduct(vector<int>& nums) {
        optional<int> dp[2] = {nullopt, nullopt};
        constexpr int INF = numeric_limits<int>::max();
        int max_product = -INF;

        for(int val : nums) {
            if(val == 0) {
                max_product = max(max_product, 0);
                dp[0] = dp[1] = nullopt;
                continue;
            }

            if(dp[0]) dp[0] = *dp[0] * val;
            if(dp[1]) dp[1] = *dp[1] * val;

            if(val < 0) swap(dp[0], dp[1]);

            if(dp[0]) dp[0] = max(*dp[0], val);
            else if(val > 0) dp[0] = val;

            if(dp[1]) dp[1] = min(*dp[1], val);
            else if(val < 0) dp[1] = val;

            max_product = max({max_product, dp[0].value_or(-INF), dp[1].value_or(-INF)});
        }

        return max_product;
    }
};