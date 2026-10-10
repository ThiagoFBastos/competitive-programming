class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        constexpr unsigned MOD = 1e9 + 7;
        const auto c = lcm<uint64_t>(a, b);

        auto count_magic_numbers = [a = (uint64_t)a, b = (uint64_t)b, c](uint64_t n) {
            return n / a + n / b - n / c;
        };

        uint64_t low = 1, high = 1llu << 62;

        while(low < high) {
            auto mid = (low + high) / 2;

            if(count_magic_numbers(mid) >= (uint64_t)n)
                high = mid;
            else
                low = mid + 1;
        }

        return (int)(high % MOD);
    }
};