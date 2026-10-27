class Solution {
public:
    int numberOfSubstrings(string s) {
        const int n = static_cast<int>(s.size());
        int low {}, substrings {};
        array<int, 3> cnt {};

        for(int i = 0; i < n; ++i) {
            const int ascii = s[i] - 'a';

            ++cnt[ascii];

            while(low < i && cnt[s[low] - 'a'] > 1) {
                --cnt[s[low] - 'a'];
                ++low;
            }

            if(*min_element(cnt.begin(), cnt.end()) > 0)
                substrings += low + 1;
        }

        return substrings;
    }
};