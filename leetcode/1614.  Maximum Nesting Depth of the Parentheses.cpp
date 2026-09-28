class Solution {
public:
    int maxDepth(string s) {
        stack<int> st;
        int max_nested {};

        st.push(0);

        for(const char ch : s) {
            if(ch == '(')
                st.push(st.top() + 1);
            else if(ch == ')') {
                max_nested = max(max_nested, st.top());
                st.pop();
            }
        }

        return max_nested;
    }
};