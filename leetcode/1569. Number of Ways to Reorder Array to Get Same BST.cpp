class Solution {
public:
    int numOfWays(vector<int>& nums) {
        constexpr int MOD = 1e9 + 7;
        const int n = static_cast<int>(nums.size());
        vector<int> fat(n + 1, 1), inv(n + 1, 1), inv_fat(n + 1, 1), dp(n + 1), sz(n + 1);
        vector<int> left(n + 1, -1), right(n + 1, -1);

        for(int i = 2; i <= n; ++i) {
            fat[i] = (long long)i * fat[i - 1] % MOD;
            inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;
            inv_fat[i] = (long long)inv[i] * inv_fat[i - 1] % MOD;
        }

        for(int i = 1; i < n; ++i) {
            const int key = nums[i];
            int root = nums.front(), last = -1;


            while(root >= 0) {
                last = root;
                if(key < root)
                    root = left[root];
                else
                    root = right[root];
            }

            if(key < last)
                left[last] = key;
            else
                right[last] = key;
        }

        auto dfs = [&](auto& self, const int u) -> void {      
            sz[u] = 1;
            dp[u] = 1;

            for(const int v : {left[u], right[u]}) {
                if(v == -1)
                    continue;
                self(self, v);
                sz[u] += sz[v];
                dp[u] = (long long)dp[u] * inv_fat[sz[v]] % MOD * dp[v] % MOD;
            }

            dp[u] = (long long)dp[u] * fat[sz[u] - 1] % MOD;
        };

        dfs(dfs, nums.front());

        return (dp[nums.front()] + MOD - 1) % MOD; 
    }
};