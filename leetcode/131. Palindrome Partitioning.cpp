class Solution {
public:
    vector<vector<string>> partition(string s) {
        const int n = static_cast<int>(s.size());
        const int m = 1 << n;
        constexpr int N = 16;
        bool is_palindrome[N][N] = {{false}};
        vector<vector<string>> partitions;

        for(int l = 0; l < n; ++l) {
            string t;
            for(int r = l; r < n; ++r) {
                t += s[r];
                is_palindrome[l][r] = t == string(t.rbegin(), t.rend());
            }
        }

        partitions.reserve(m);

        for(int i = (1 << (n - 1)); i < m; ++i) {
            int low = 0;
            bool is_partitioned = true;
            vector<string> partition;
            string t;

            partition.reserve(n);

            for(int j = 0; j < n && is_partitioned; ++j) {
                t += s[j];
                if((i >> j) & 1) {
                    is_partitioned = is_partitioned && is_palindrome[low][j];
                    partition.push_back(t);      
                    low = j + 1;
                    t.clear();
                }
            }

            if(!is_partitioned)
                continue;

            partitions.push_back(partition);
        }

        return partitions;
    }
};