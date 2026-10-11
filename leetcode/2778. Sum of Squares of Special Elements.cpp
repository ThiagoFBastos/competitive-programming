class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        const auto n = nums.size();

        auto rng = views::zip(views::iota(size_t {1}, n + 1), nums) | views::filter([n](const auto& p) {
            const auto [index, val] = p;
            return n % index == 0;
        }) | views::transform([](const auto& p) {
            const auto [index, val] = p;
            return val * val;
        });

        const int sum = ranges::fold_left(rng, 0, plus<int>());

        return sum;
    }
};