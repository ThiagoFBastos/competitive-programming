class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        const int n = static_cast<int>(s.size());
        const int m = 1 << n;
        vector<string> answer;

        answer.reserve(m);

        for(int i = 0; i < m; ++i) {
            string t;
            bool is_unique = true;

            for(int j = 0; j < n; ++j) {
                if(isalpha(s[j])) {
                    t += (i >> j) & 1 ? toupper(s[j]) : tolower(s[j]);
                } else if((i >> j) & 1) {
                    is_unique = false;
                    break;
                } else
                    t += s[j];
            }

            if(is_unique)
                answer.push_back(t);
        }

        return answer;
    }
};