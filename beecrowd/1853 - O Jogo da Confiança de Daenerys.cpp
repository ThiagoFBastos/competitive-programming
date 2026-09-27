#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

constexpr int K = 10;

struct Vertex {
    int next[K];
    int go[K];
    int par;
    int link;
    bool leaf;
    char ch;
    int next_leaf;
    
    Vertex(int p, char ch = '$'): 
		par {p}, 
		link {},
		leaf {},
        ch {ch},
		next_leaf {-1} 
	{
        memset(next, -1, sizeof next);
        memset(go, -1, sizeof go);
    }
};

struct Aho {
    vector<Vertex> st;

    Aho() = default;

    Aho(const vector<string>& words) {
        st.emplace_back(0);
        st.back().next_leaf = 0;
        for(const auto& s : words) push(s);
        bfs();
    }

    void push(const string& s) {
        int no = 0;
        for(char ch : s) {
            int pos = ch - 'a';
            if(st[no].next[pos] == -1) {
                st[no].next[pos] = st.size();
                st.emplace_back(no, pos);
            }
            no = st[no].next[pos];
        }
        st[no].leaf = true;
    }

    void bfs() {
        queue<int> q;

        q.push(0);
        for(int i = 0; i < K; ++i) st[0].next[i] = max(0, st[0].next[i]);

        while(!q.empty()) {
            int from = q.front();
            q.pop();
            
            auto& no = st[from];
            char e = no.ch;
            int par = no.par;

            if(par) {    
                for(int v = st[no.par].link; v >= 0; v = st[v].link) {
                    const auto& n = st[v];
                    if(n.next[(int)e] != -1) {
                        no.link = n.next[(int)e];
                        break;
                    }
                }
            }

            for(int i = 0; i < K; ++i) {
                int next = no.next[i];
                if(next <= 0) continue;
                q.push(next);
            }
        }
    }

    int go(int no, int ch) {
        auto& v = st[no];
        if(v.go[ch] != -1) return v.go[ch];
        return v.go[ch] = v.next[ch] != -1 ? v.next[ch] : go(v.link, ch);
    }

    int nextLeaf(int no) {
        auto& v = st[no];
        if(v.next_leaf != -1) return v.next_leaf;
        return v.next_leaf = st[v.link].leaf ? v.link : nextLeaf(v.link);
    }

    int countNodes() const noexcept {
        return st.size();
    }
};


constexpr int N = 51;
constexpr int M = 1e5 + 100;

char g[N][M];
int D, L, S;

Aho aho;

int DP(int f, int no) {
    if(g[f][no] != -1) return g[f][no];
    bitset<K + 1> mex;
    for(int i = 0; i < L; ++i) mex[DP(f - 1, aho.go(no, i))] = 1;
    g[f][no] = 0;
    while(mex[g[f][no]]) ++g[f][no];
    return g[f][no];
}

void solve() {

    cin >> D >> L;

    vector<string> adj(D);

    for(auto& s : adj) cin >> s;

    aho = Aho(adj);

    int nos = aho.countNodes(), XOR = 0;

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < nos; ++j)
            g[i][j] = aho.st[j].leaf || aho.nextLeaf(j) ? 0 : -1;

    for(int i = 0; i < nos; ++i) g[0][i] = 0;

    cin >> S;

    while(S--) {
        string s;
        int f;
        cin >> s >> f;
        int no = 0;
        for(char ch : s) no = aho.go(no, ch - 'a');    
        XOR ^= DP(f, no);
    }

    cout << (XOR ? "Tyrion\n" : "Daenerys\n");
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}