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
vi st;
int res = 1e18;


void dfs(int t) {
    if (st.empty()) {
        res = min(res, t);
        return;
    }
    sort(st.begin(), st.end(), [](int x, int y) {
        return w[x] < w[y];
    });
    vi tst = st;
    st.clear();
    for (int i = 0; i < tst.size(); i++) {
        int r = t + w[tst[i]];
        for (int j : g[tst[i]]) {
            d[j]--;
            if (!d[j]) st.push_back(j);
        }
        dfs(r);
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
    for (int i = 1; i <= n; i++)
        if (!d[i]) st.push_back(i);
    dfs(0);
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