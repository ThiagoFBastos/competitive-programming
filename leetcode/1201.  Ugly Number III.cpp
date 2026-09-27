class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        auto ab = lcm<long long>(a, b);
        auto ac = lcm<long long>(a, c);
        auto bc = lcm<long long>(b, c);
        auto abc = lcm<long long>(ab, c);

        auto count_numbers = [=](long long x) {
            return x / a + x / b + x / c - x / ab - x / ac - x / bc + x / abc;
        };

        long long low = 1, high = 2e9;

        while(low < high) {
            auto mid = (low + high) / 2;

            if(count_numbers(mid) >= n)
                high = mid;
            else
                low = mid + 1;
        }

        return static_cast<int>(high);
    }
};