class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        auto count_diff_pairs = [&](int dist) {
            const int n = static_cast<int>(nums.size());
            int low = 0, pairs = 0;

            for(int i = 0; i < n; ++i) {
                while(low < i && nums[i] - nums[low] > dist)
                    ++low;

                pairs += i - low; 
            }

            return pairs;
        };

        constexpr int MAX_DIST = 1e6;
        int low = 0, high = MAX_DIST;

        while(low < high) {
            int mid = (low + high) / 2;

            if(count_diff_pairs(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return high;
    }
};