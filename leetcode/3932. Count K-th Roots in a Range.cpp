class Solution {
public:
    int countKthRoots(int l, int r, int k) {
        return countPerfectKthRoots(r, k) - countPerfectKthRoots(l - 1, k);
    }

private:
    int countPerfectKthRoots(int n, int k) {
        int lo = 0, hi = n;

        if(n < 0)
            return 0;

        while(lo < hi) {
            const int mid = (lo + hi + 1) / 2;
            long long power {1};
            bool is_too_high {};

            for(int i = 0; i < k; ++i) {
                power *= mid;
                if(power > n) {
                    is_too_high = true;
                    break;
                }
            }

            if(is_too_high)
                hi = mid - 1;
            else
                lo = mid;
        }

        return hi + 1;
    }
};