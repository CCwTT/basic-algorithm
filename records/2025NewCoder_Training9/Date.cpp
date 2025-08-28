#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define int long long
#define endl '\n'

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int N = 30;
int n, m;
int w[N], d[N];
vector<vi> g(N);
int res = 1e18;

struct cmp {
    bool operator()(int x, int y) const {
        return w[x] < w[y];
    }
};


void dfs(int acc, set<int, cmp> st) {
    if(acc>=res) return;
    if (st.size()==0) {
        res = min(res, acc);
        return;
    }
    set<int, cmp> nst = st;
    for (auto i : st) {
        nst.erase(i);
        for (auto j : g[i]) {
            d[j]--;
            if (!d[j]) nst.insert(j);
        }
        dfs(acc + w[i], nst);
    }
    for (auto i : st) {
        for (auto j : g[i]) d[j]++;
    }
}


void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        d[v]++;
    }
    set<int, cmp> st;
    for (int i = 1; i <= n; i++)
        if (!d[i]) st.insert(i);
    dfs(0, st);
    cout << res << endl;
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
