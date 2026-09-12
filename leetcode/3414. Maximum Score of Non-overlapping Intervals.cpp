struct Event {
    int x;
    int type;
    int index;
    int weight;

    Event() = default;

    Event(int _x, int _type, int _index, int _weight)
        : x(_x)
        , type(_type)
        , index(_index)
        , weight(_weight)
    {

    }

    bool operator<(const Event& other) const {
        return x < other.x || (x == other.x && type < other.type);
    }
};

struct Candidate {
    vector<int> indexes;
    long long sum_weight {};

    Candidate add(int weight, int index) {
        Candidate ans = *this;
        ans.sum_weight += weight;
        ans.indexes.push_back(index);
        sort(ans.indexes.begin(), ans.indexes.end());
        return ans;
    }

    bool isBetter(const Candidate& other) const {
        if(indexes.empty())
            return false;
        else if(sum_weight != other.sum_weight)
            return sum_weight > other.sum_weight;
        return indexes < other.indexes;
    }
};

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        const int n = static_cast<int>(intervals.size());
        array<Candidate, 4> candidates;
        vector<Event> events;
        vector<array<Candidate, 4>> usingAsCandidate(n);
        int i = 0;

        events.reserve(2 * n);

        for(const auto& interval : intervals) {
            int l = interval[0], r = interval[1], weight = interval[2];
            events.emplace_back(l, 0, i, weight);
            events.emplace_back(r, 1, i, 0);
            ++i;
        }

        sort(events.begin(), events.end());

        for(const auto& [x, type, index, weight] : events) {
            if(type == 0) {
                usingAsCandidate[index][0] = Candidate().add(weight, index);
                for(int i = 1; i < 4; ++i)
                    usingAsCandidate[index][i] = candidates[i - 1].add(weight, index);
            } else {
                for(int i = 0; i < 4; ++i) {
                    if(usingAsCandidate[index][i].isBetter(candidates[i]))
                        candidates[i] = move(usingAsCandidate[index][i]);
                }
            }
        }

        auto answer = candidates[0];

        for(int i = 1; i < 4; ++i) {
            if(candidates[i].isBetter(answer))
                answer = move(candidates[i]);
        }

        return answer.indexes;
    }
};