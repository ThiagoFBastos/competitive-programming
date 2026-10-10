class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        vector<pair<long long, int>> min_queue(1, make_pair(0LL, 0));
        long long sum = 0;
        const int n = static_cast<int>(nums.size());
        constexpr int INF = numeric_limits<int>::max();
        int answer = INF;

        for(int i = 1; i <= n; ++i) {
            sum += nums[i - 1];

            auto it = upper_bound(min_queue.begin(), min_queue.end(), make_pair(sum - k, n + 1));

            if(it != min_queue.begin()) {
                const auto [prefix, index] = *prev(it);
                answer = min(answer, i - index);
            }

            while(!min_queue.empty() && min_queue.back().first >= sum)
                min_queue.pop_back();

            min_queue.emplace_back(sum, i);
        }

        return answer != INF ? answer : -1;
    }
};