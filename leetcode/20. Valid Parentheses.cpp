class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        const char open_brackets[] = {'(', '{', '['};
        const char close_brackets[] = {')', '}', ']'};

        for(const char ch : s) {
            if(count(open_brackets, open_brackets + 3, ch))
                st.emplace(ch);
            else {
                if(st.empty())
                    return false;

                auto index = find(close_brackets, close_brackets + 3, ch) - close_brackets;

                if(st.top() != open_brackets[index])
                    return false;

                st.pop();
            }
        }

        return st.empty();
    }
};