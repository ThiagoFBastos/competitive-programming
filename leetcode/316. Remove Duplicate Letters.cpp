class Solution {
public:
    string removeDuplicateLetters(string s) {
        array<int, 26> cnt {};

        for(const char c : s)
            ++cnt[c - 'a'];

        string answer;

        for(const char ch : s) {
            const int ord = ch - 'a';
            
            --cnt[ord];

            if(count(answer.begin(), answer.end(), ch) > 0)
                continue;

            bool inserted {};

            for(size_t i = 0; i < answer.size(); ++i) {
                if(answer[i] < ch)
                    continue;
                    
                auto rng = views::iota(i, answer.size()) | views::transform([&](const int index) {
                    const int ord = answer[index] - 'a';
                    return cnt[ord];
                });

                auto it = ranges::min_element(rng);

                if(ranges::end(rng) != it && *it > 0) {
                    inserted = true;
                    answer[i] = ch;
                    answer.erase(i + 1, answer.size());
                    break;
                }
            }

            if(!inserted)
                answer.push_back(ch);
        }

        return answer;
    }
};