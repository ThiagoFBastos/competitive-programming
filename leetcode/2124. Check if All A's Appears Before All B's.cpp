class Solution {
public:
    bool checkString(string s) {
        auto idxA = s.rfind('a');
        auto idxB = s.find('b');

        return !(idxA != string::npos && idxB != string::npos && idxA > idxB);
    }
};