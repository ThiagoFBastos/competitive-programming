#include <bits/stdc++.h>

using namespace std;

class HopcroftKarp
{
public:
    HopcroftKarp(int m, int n):
        _adjU(m + 1),
        _pairU(m + 1),
        _pairV(n + 1),
        _dist(m + 1),
        _m(m),
        _n(n)
    {

    }

    void add_edge(int u, int v)
    {
        _adjU[u].emplace_back(v);
    }

    const std::vector<int>& pairU() const 
    {
        return _pairU;
    }

    int hopcroftKarp() 
    {
        int result = 0;

        while(bfs()) 
        {
            for(int u = 1; u <= _m; ++u) 
            {
                if(_pairU[u] == 0 && dfs(u)) 
                    ++result;
            }
        }

        return result;
    }

private:
    bool bfs() 
    {
        std::queue<int> q;

        for(int u = 1; u <= _m; ++u) 
        {
            if(_pairU[u] == 0) 
            {
                _dist[u] = 0;
                q.push(u);
            } else 
                _dist[u] = INF;
        }

        _dist[0] = INF;
        
        while(!q.empty()) 
        {
            int u = q.front();

            q.pop();

            if(_dist[u] >= _dist[0]) 
                continue;

            for(int v : _adjU[u]) 
            {
                if(_dist[_pairV[v]] == INF) 
                {
                    _dist[_pairV[v]] = _dist[u] + 1;
                    q.push(_pairV[v]);
                }
            }
        }

        return _dist[0] != INF;
    }

    bool dfs(int u) 
    {
        if(!u) 
            return true;

        for(int v : _adjU[u]) 
        {
            if(_dist[_pairV[v]] == _dist[u] + 1) 
            {
                if(dfs(_pairV[v])) 
                {
                    _pairV[v] = u;
                    _pairU[u] = v;
                    return true;
                }
            }		
        }

        _dist[u] = INF;

        return false;
    }

    static constexpr int INF = 1e9;

    std::vector<std::vector<int>> _adjU;

    std::vector<int> _pairU;

    std::vector<int> _pairV;

    std::vector<int> _dist;

    int _m;

    int _n;
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, e;

    cin >> n >> m >> e;

    HopcroftKarp hk(m, n);

	while(e--) {
		int a, b;
		cin >> a >> b;
		++a, ++b;
		hk.add_edge(b, a);
	}

	cout << hk.hopcroftKarp() << '\n';

    const auto& pairU = hk.pairU();

	for(int u = 1; u <= m; ++u) {
		if(!pairU[u]) continue;
		cout << pairU[u] - 1 << ' ' << u - 1 << '\n';
	}

    return 0;
}