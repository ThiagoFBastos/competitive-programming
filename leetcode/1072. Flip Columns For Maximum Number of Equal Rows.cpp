class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        map<vector<int>, int> frequency;
        int answer {};

        auto complement = [](vector<int> row) {
            for(int& val : row)
                val ^= 1;
            return row;
        };

        for(const auto& row : matrix)
            ++frequency[row];

        for(const auto& [key, cnt] : frequency) {
            auto it = frequency.find(complement(key));
            int total {cnt};

            if(it != frequency.end())
                total += it->second;

            answer = max(answer, total);
        }

        return answer;
    }
};