class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int answer = 0, k = 0;

        while(left && right) {
            int diff = right - left;
            
            if(diff == 0 && left % 2)
                answer |= 1 << k;
            
            ++k;
            left >>= 1;
            right >>= 1;
        }

        return answer;
    }
};