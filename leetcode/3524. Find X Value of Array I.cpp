class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        const auto n = nums.size();
        vector<long long> cnt(k, 0);
        constexpr int K = 5;

        for(int i = 0; i < k; ++i) {
            array<int, K> product {};

            for(int val : nums) {
                array<int, K> newProduct {};
                int mod = val % k;

                ++newProduct[mod];

                for(int j = 0; j < k; ++j)
                    newProduct[j * mod % k] += product[j];

                product = move(newProduct);

                cnt[i] += product[i];
            }
        }

        return cnt;
    }
};