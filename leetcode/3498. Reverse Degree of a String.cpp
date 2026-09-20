class Solution {
public:
    int reverseDegree(string s) {
        const int n = static_cast<int>(s.size());

        auto rng = views::zip(views::iota(1, n + 1), s) | views::transform([](const auto& p) {
            auto [index, chr] = p;
            return index * (26 - chr + 'a');
        });

        auto sum = ranges::fold_left(rng, 0, plus<int>());

        return sum;
    }
};