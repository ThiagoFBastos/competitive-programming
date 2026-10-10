class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> frequency;
        map<int, int> st;
        int cnt = 0, answer = 0;

        frequency.reserve(nums.size());

        for(const int val : nums) {
            ++cnt;

            if(auto it = frequency.find(val); it != frequency.end()) {
                auto stIt = st.find(it->second);

                if(--stIt->second == 0)
                    st.erase(stIt);
            }

            int frq = ++frequency[val];
            ++st[frq];

            if(st.size() == 1) {
                if(st.begin()->first == 1 || st.begin()->second == 1)
                    answer = cnt;
            } else if(st.size() == 2) {
                int first = st.begin()->first;
                int last = st.rbegin()->first;

                if(first == last - 1 && st.rbegin()->second == 1)
                    answer = cnt;

                if(st.begin()->first == 1 && st.begin()->second == 1)
                    answer = cnt;
            }
        }

        return answer;
    }
};