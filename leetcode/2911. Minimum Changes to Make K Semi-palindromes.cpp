class Solution {
public:
    int minimumChanges(string s, int k) {
        constexpr int INF = static_cast<int>(1e9);
        const int n = static_cast<int>(s.size());
        vector<vector<int>> semi(n, vector<int>(n, INF));
        vector<int> dp(n + 1, INF);

        for(int d = 1; d <= n; ++d) {
            for(int len = 2 * d; len <= n; len += d) {

                for(int l = 0; l + len <= n; ++l) {
                    int r = l + len - 1;
                    int answer {};

                    for(int i = 0; i < d; ++i) {
                        const int cnt = (len - 1 - i) / d;
                        int low = i, high = i + cnt * d;

                        while(low < high) {
                            if(s[l + low] != s[l + high])
                                ++answer;

                            low += d;
                            high -= d;
                        }
                    }

                    semi[l][r] = min(semi[l][r], answer);                    
                }
            }
        }

        dp[0] = 0;

        vector<int> tmp(n + 1);

        for(int i = 0; i < k; ++i) {
            fill(tmp.begin(), tmp.end(), INF);

            for(int l = 0; l < n; ++l)
                for(int r = l + 1; r < n; ++r)
                    tmp[r + 1] = min(tmp[r + 1], dp[l] + semi[l][r]);

            swap(dp, tmp);
        }

        return dp.back();
    }
};