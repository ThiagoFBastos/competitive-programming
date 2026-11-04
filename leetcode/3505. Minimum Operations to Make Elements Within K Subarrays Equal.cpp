class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        const int n = static_cast<int>(nums.size());
        constexpr long long INF = 1e15L;
        vector<vector<long long>> dp(n + 1, vector<long long>(k, INF));
        set<pair<int, int>> low, high;
        long long lowSum {}, highSum {};

        for(int i = 0; i < x - 1; ++i) {
            high.emplace(nums[i], i);
            highSum += nums[i];
        }

        for(int i = x - 1; i < n; ++i) {
            if(i >= x) {
                const auto p = make_pair(nums[i - x], i - x);

                if(auto it = high.find(p); it != high.end()) {
                    high.erase(it);
                    highSum -= p.first;
                }

                if(auto it = low.find(p); it != low.end()) {
                    low.erase(it);
                    lowSum -= p.first;
                }
            }

            high.emplace(nums[i], i);
            highSum += nums[i];

            while(low.size() < high.size()) {
                const int val = high.begin()->first;
                lowSum += val;
                highSum -= val;
                low.insert(*high.begin());
                high.erase(high.begin());
            }

            while(low.rbegin()->first > high.begin()->first) {
                const auto x = *low.rbegin();
                const auto y = *high.begin();

                lowSum += y.first - x.first;
                highSum += x.first - y.first;

                low.erase(x);
                low.insert(y);
                high.erase(y);
                high.insert(x);
            }

            const long long lowCount = static_cast<long long>(low.size());
            const long long highCount = static_cast<long long>(high.size());
            const long long median = low.rbegin()->first;

            const long long operations = median * lowCount - lowSum + highSum - highCount * median;

            dp[i + 1][0] = min(operations, dp[i][0]);

            for(int j = 1; j < k; ++j)
                dp[i + 1][j] = min(dp[i][j], operations + dp[i + 1 - x][j - 1]);
        }

        long long answer = INF;

        for(const auto& values : dp)
            answer = min(answer, values[k - 1]);

        return answer;
    }
};