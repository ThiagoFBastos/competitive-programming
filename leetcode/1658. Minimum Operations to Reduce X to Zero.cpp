class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        const int n = static_cast<int>(nums.size());
        constexpr int INF = numeric_limits<int>::max();
        int high = n, answer = INF;
        int suffix = 0, prefix = 0;

        while(high > 0 && suffix < x)
            suffix += nums[--high];

        if(suffix == x)
            answer = min(answer, n - high);
        else if(suffix < x)
            return -1;

        for(int i = 0; i < n; ++i) {
            if(high == i) {
                suffix -= nums[i];
                ++high;
            }

            prefix += nums[i];

            while(prefix + suffix > x && high < n)
                suffix -= nums[high++];
            
            if(prefix + suffix == x)
                answer = min(answer, i + 1 + n - high);
        }

        return answer != INF ? answer : -1;
    }
};