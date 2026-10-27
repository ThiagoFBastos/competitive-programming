class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());

        int low {}, answer {};
        const int n = static_cast<int>(trainers.size());

        for(const int ability : players) {
            while(low < n && ability > trainers[low])
                ++low;

            if(low < n) {
                ++answer;
                ++low;
            }
        }

        return answer;
    }
};