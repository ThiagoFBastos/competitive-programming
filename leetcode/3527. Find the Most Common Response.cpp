class Solution {
public:
    string findCommonResponse(vector<vector<string>>& responses) {
        map<string, int> frequency;

        for(auto& res : responses) {
            ranges::sort(res);
            auto it = unique(res.begin(), res.end());
            res.erase(it, res.end());

            for(const auto& s : res)
                ++frequency[s];
        }

        const int max_frequency = ranges::fold_left(frequency | views::values, 0, ranges::max);

        auto it = find_if(frequency.begin(), frequency.end(), [max_frequency](auto& p) {
            return p.second == max_frequency;
        });

        return it->first;
    }
};