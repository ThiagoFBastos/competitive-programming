class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> frq;

        frq.reserve(nums.size());

        for(const int val : nums)
            ++frq[val];

        vector<pair<int, int>> elements(frq.begin(), frq.end());

        sort(elements.begin(), elements.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.second > rhs.second;
        });

        auto values = elements | views::take(k) | views::keys | ranges::to<vector<int>>();

        return values;
    }
};