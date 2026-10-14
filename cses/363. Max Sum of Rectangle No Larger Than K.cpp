class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        const int n = static_cast<int>(matrix.size());
        const int m = static_cast<int>(matrix[0].size());

        vector<vector<int>> prefix(n, vector<int>(m + 1, 0));
        int answer = numeric_limits<int>::min();

        auto merge = [sum = k](auto& prefix, const int lo, const int hi) {
            const int n = hi - lo + 1, mid = (lo + hi) / 2;
            int i = lo, j = mid + 1, k = 0, answer = numeric_limits<int>::min();
            constexpr int N = 101;
            int tmp[N];
            
            for(int pos = hi, low = mid + 1; pos > mid; --pos) {
                while(low > lo && prefix[pos] - prefix[low - 1] <= sum)
                    --low;

                if(low <= mid)
                    answer = max(answer, prefix[pos] - prefix[low]);
            }

            while(i <= mid && j <= hi)
                tmp[k++] = prefix[i] < prefix[j] ? prefix[i++] : prefix[j++];

            while(i <= mid)
                tmp[k++] = prefix[i++];

            while(j <= hi)
                tmp[k++] = prefix[j++];

            copy(begin(tmp), begin(tmp) + n, prefix.begin() + lo);

            return answer;
        };

        auto merge_sort = [k, merge](auto& self, auto& prefix, const int lo, const int hi) -> int {
            if(lo == hi)
                return lo && prefix[lo] <= k ? prefix[lo] : numeric_limits<int>::min();
            
            const int mid = (lo + hi) / 2;

            const int lhs = self(self, prefix, lo, mid);
            const int rhs = self(self, prefix, mid + 1, hi);
            const int result = merge(prefix, lo, hi);

            return max({lhs, rhs, result});
        };

        for(int i = 0; i < n; ++i)
            for(int j = 1; j <= m; ++j)
                prefix[i][j] = prefix[i][j - 1] + matrix[i][j - 1];

        for(int l = 1; l <= m; ++l) {
            for(int r = l; r <= m; ++r) {
                vector<int> prefix_sum(n + 1, 0);

                for(int i = 1; i <= n; ++i)
                    prefix_sum[i] = prefix_sum[i - 1] + prefix[i - 1][r] - prefix[i - 1][l - 1];

                answer = max(answer, merge_sort(merge_sort, prefix_sum, 0, n));
            }
        }

        return answer;
    }
};