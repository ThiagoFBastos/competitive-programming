class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        const auto n = nums.size();
        unordered_map<int, int> diff_pos;
        int diff {}; 
        size_t answer = 0;

        diff_pos.reserve(n + 1);
        diff_pos[0] = 0;

        for(decay_t<decltype(n)> i = 1; i <= n; ++i) {
            diff += nums[i - 1] == 0 ? -1 : 1;

            if(auto it = diff_pos.find(diff); it != diff_pos.end())
                answer = max(answer, i - it->second);

            diff_pos.emplace(diff, i);
        }

        return static_cast<int>(answer);
    }
};