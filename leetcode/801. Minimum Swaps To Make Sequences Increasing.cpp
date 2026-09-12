class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        const auto n =  nums1.size();
        vector<array<int, 2>> dp(n);
        constexpr int INF = 1e9;

        dp[0][0] = 0;
        dp[0][1] = 1;

        for(size_t i = 1; i < n; ++i) {
            dp[i][0] = dp[i][1] = INF;

            for(int j = 0; j < 2; ++j) {
                int last_1 = nums1[i - 1], last_2 = nums2[i - 1];

                if(j)
                    swap(last_1, last_2);

                for(int k = 0; k < 2; ++k) {
                    int cur_1 = nums1[i], cur_2 = nums2[i];

                    if(k)
                        swap(cur_1, cur_2);

                    dp[i][k] = min(dp[i][k], cur_1 > last_1 && cur_2 > last_2 ? dp[i - 1][j] + k : INF);
                }
            }
        }

        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};