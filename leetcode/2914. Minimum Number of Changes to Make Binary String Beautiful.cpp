class Solution {
public:
    int minChanges(string s) {
        const int n = static_cast<int>(s.size());
        int answer {};

        for(int i = 0; i < n; i += 2)
            answer += s[i] ^ s[i + 1];
        
        return answer;
    }
};