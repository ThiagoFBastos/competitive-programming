class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        constexpr int N = 1e5 + 5;
        vector<int> cnt(N, 0);
        long long answer = 0;
        const int n = static_cast<int>(nums1.size());

        for(int i = 0; i < n; ++i) {
            int diff = abs(nums1[i] - nums2[i]);
            ++cnt[diff];
            answer += (long long)diff * diff;
        }

        int operations = k1 + k2;

        for(int i = N - 1; i > 0 && operations; --i) {
            if(!cnt[i])
                continue;

            int apply = min(cnt[i], operations);

            operations -= apply;
            answer -= (2ll * i - 1) * apply;
            cnt[i - 1] += apply;
        }

        return answer;
    }
};