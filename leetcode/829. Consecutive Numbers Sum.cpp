class Solution {
public:
    int consecutiveNumbersSum(int n) {
        auto divisors = [](int n) {
            vector<int> nums;

            for(int i = 1; i * i <= n; ++i) {
                if(n % i)
                    continue;

                nums.emplace_back(i);

                if(i * i != n)
                    nums.emplace_back(n / i);
            }

            return nums;
        };

        const auto nums = divisors(2 * n);
        int sequences {};

        for(int a : nums) {
            int b = 2 * n / a;

            if(a > b)
                swap(a, b);

            int r = a + b - 1;

            if(r & 1) continue;

            r >>= 1;

            int l = b - r;

            if(l <= r)
                ++sequences;
        }

        return sequences / 2;
    }
};