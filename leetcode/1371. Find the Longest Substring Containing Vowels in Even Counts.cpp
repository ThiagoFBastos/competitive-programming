class Solution {
public:
    int findTheLongestSubstring(string s) {
        constexpr int N = 32;
        array<optional<int>, N> loc {};
        int frequency {}, answer {};
        constexpr char vowels[] = {'a', 'e', 'i', 'o', 'u'};
        const int n = static_cast<int>(s.size());

        loc[0] = 0;

        for(int i = 1; i <= n; ++i) {
            const char ch = s[i - 1];
            auto it = find(begin(vowels), end(vowels), ch);

            if(it != end(vowels)) {
                const int pos = it - vowels;
                frequency ^= 1 << pos;
            }

            if(loc[frequency])
                answer = max(answer, i - *loc[frequency]);
            else
                loc[frequency] = i;
        }

        return answer;
    }
};