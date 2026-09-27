class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;

        st.emplace();

        for(char ch : s) {
            if(ch == '(')
                st.emplace();
            else if(ch == ')') {
                auto str = st.top();
                st.pop();
                reverse(str.begin(), str.end());
                st.top() += str;
            } else
                st.top() += ch;
        }

        return st.top();
    }
};