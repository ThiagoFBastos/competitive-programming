class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        const int n = static_cast<int>(words.size());
        const int m = 1 << n;
        constexpr int ALPHA = 26;

        array<int, ALPHA> cnt {};
        vector<array<int, ALPHA>> frequency(m);
        vector<int> total_score(m);
        vector<bool> suitable(m);
        int max_score {};

        for(const char ch : letters)
            ++cnt[ch - 'a'];

        frequency[0].fill(0);
        total_score[0] = 0;
        suitable[0] = true;

        for(int i = 1; i < m; ++i) {
            int j = __builtin_ctz(i);
            int mask = i ^ (1 << j);

            if(!suitable[mask])
                continue;

            frequency[i] = frequency[mask];
            total_score[i] = total_score[mask];
            suitable[i] = true;

            for(const char ch : words[j]) {
                const int ord = ch - 'a';
                if(++frequency[i][ord] > cnt[ord]) {
                    suitable[i] = false;
                    break;
                }
                total_score[i] += score[ord];
            }

            if(suitable[i])
                max_score = max(max_score, total_score[i]);
        }

        return max_score;
    }
};