class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        using ServerType = pair<long long, int>;

        const int n = static_cast<int>(servers.size());
        const int m = static_cast<int>(tasks.size());
        priority_queue<ServerType, vector<ServerType>, greater<ServerType>> serversQueue, serversWaiting;
        vector<int> answer(m);

        for(int i = 0; i < n; ++i)
            serversQueue.emplace(servers[i], i);

        long long int t = 0;

        for(int i = 0; i < m; ++i) {
            t = max<long long>(t, serversQueue.empty() ? max<long long>(i, serversWaiting.top().first) : i);

            while(!serversWaiting.empty() && serversWaiting.top().first <= t) {
                const auto [t, index] = serversWaiting.top();
                serversWaiting.pop();
                serversQueue.emplace(servers[index], index);
            }

            const auto [_, index] = serversQueue.top();
            serversQueue.pop();

            answer[i] = index;

            serversWaiting.emplace(t + tasks[i], index);
        }

        return answer;
    }
};