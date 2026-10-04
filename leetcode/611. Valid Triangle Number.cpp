#define check(a, b, c) (a + b > c)

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        int triples {};

        sort(nums.begin(), nums.end());

        for(int i = 0; i < n; ++i) {
            int high = i + 1;
            for(int j = i + 1; j < n - 1; ++j) {
                while(high + 1 < n && check(nums[i], nums[j], nums[high + 1]))
                    ++high;

                if(check(nums[i], nums[j], nums[j + 1]))
                    triples += high - j;
            }
        }

        return triples;
    }
};