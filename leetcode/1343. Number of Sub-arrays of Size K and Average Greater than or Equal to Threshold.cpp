class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        const int n = static_cast<int>(arr.size());
        vector<int> prefix(n + 1);
        int answer {};

        transform(arr.begin(), arr.end(), arr.begin(), [threshold](const int value) {
            return value - threshold;
        });

        partial_sum(arr.begin(), arr.end(), next(prefix.begin()), plus<int>());

        for(int i = k; i <= n; ++i) {
            if(prefix[i] - prefix[i - k] >= 0)
                ++answer;
        }

        return answer;
    }
};