class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        const int n = static_cast<int>(nums.size());
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> uid(0, (1 << n) - 1);

        auto to_str = [n](int mask) {
            string s;

            for(; mask; mask >>= 1)
                s += char(mask % 2 + '0');

            while((int)s.size() < n)
                s += '0';

            reverse(s.begin(), s.end());

            return s;
        };

        sort(nums.begin(), nums.end());

        while(true) {
            int mask = uid(rng);
            const auto s = to_str(mask);
            if(!binary_search(nums.begin(), nums.end(), s))
                return s;
        }

        throw exception();
        return "";
    }
};