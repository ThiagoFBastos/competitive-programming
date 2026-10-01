#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

constexpr int N = 1e4 + 100;

struct FN {
    i64 a, b;

    i64 evaluate(i64 x) const {
        return a * x + b;
    }

    bool operator<(const FN& other) const {
        return a < other.a || (a == other.a && b < other.b);
    }
};

vector<FN> st[4 * N];
FN f[N];

struct CHTMergeSortTree {
    int n;

    bool overshadow(const FN& a, const FN& b, const FN& c) const {
        if(a.a == b.a || b.a == c.a)
			return true;

		i128 num1 = a.b - b.b;
		i128 den1 = b.a - a.a;

		i128 num2 = b.b - c.b;
		i128 den2 = c.a - b.a;

		return num1 * den2 <= num2 * den1;
    }

    void merge(vector<FN>& dest, const vector<FN>& left, const vector<FN>& right) {
        int n = left.size(), m = right.size();
        int i = n - 1, j = m - 1, k = 0;

        dest.resize(n + m);

        while(i >= 0 && j >= 0) {
            const auto& nw = left[i] < right[j] ? left[i--] : right[j--];
            while(k >= 2 && overshadow(nw, dest[k - 1], dest[k - 2])) --k;
            dest[k++] = nw;
        }

        while(i >= 0) {
            while(k >= 2 && overshadow(left[i], dest[k - 1], dest[k - 2])) --k;
            dest[k++] = left[i--];
        }

        while(j >= 0) {
            while(k >= 2 && overshadow(right[j], dest[k - 1], dest[k - 2])) --k;
            dest[k++] = right[j--];
        }

        dest.resize(k);
        reverse(all(dest));
    }

    void build(FN f[], int l, int r, int p = 1) {
        if(l == r) { st[p] = {f[l]}; return;}
        int m = (l + r) >> 1;
        build(f, l, m, 2 * p);
        build(f, m + 1, r, 2 * p + 1);
        merge(st[p], st[2 * p], st[2 * p + 1]);
    }

    //It has to be in ascending/descending order of x.
    i64 query(int x, int l, int r, int lo, int hi, int p = 1) {
        if(l > r || lo > hi || r < lo || l > hi) return -INFLL;
        else if(lo >= l && hi <= r) {
            auto& X = st[p];
            while((int)X.size() >= 2) {
                const FN& l1 = X.back(), &l2 = *(X.end() - 2);
                if(l1.evaluate(x) > l2.evaluate(x)) break;
                X.pop_back();
            }
            return X.back().evaluate(x);
        }
        int m = (lo + hi) >> 1;
        i64 v1 = query(x, l, r, lo, m, 2 * p);
        i64 v2 = query(x, l, r, m + 1, hi, 2 * p + 1);
        return max(v1, v2);
    }

    i64 query(int x, int l, int r) {
        return query(x, l, r, 0, n - 1);
    }

    CHTMergeSortTree(FN* be, FN* en) {
        n = en - be;
        build(be, 0, n - 1);
    }
};

i64 dp[N];
int n_products, target;

void solve() {

    cin >> n_products >> target;

    vector<int> a(n_products), b(n_products);

    for(int& v : a) cin >> v;
    for(int& v : b) cin >> v;

    fill(dp, dp + N, -INFLL);
    dp[0] = 0;

    for(int i = 0; i < n_products; ++i) {

        for(int j = 0; j <= target; ++j) f[j] = {-2 * j, dp[j] + j * j};
		
        CHTMergeSortTree cht(f, f + target + 1);		

        for(int j = 0; j < a[i]; ++j) dp[j] = -INFLL;

        for(int j = a[i]; j <= target; ++j)
            dp[j] = cht.query(j, max(0, j - b[i]), j - a[i]) + j * j;
    }

    if(dp[target] < 0) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    cout << dp[target] << '\n';
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}