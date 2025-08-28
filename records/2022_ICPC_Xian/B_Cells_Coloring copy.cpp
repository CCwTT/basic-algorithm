#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

template <typename T>
struct Flow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<int> cur, h;
    
    Flow(const int &n = 0) : n(n), g(n) {}
    
    bool bfs(int s, int t) {
        h.assign(n, -1);
        queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T maxflow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, c, d;
    cin >> n >> m >> c >> d;

    const int N = n + m;
    int s = N, t = N + 1;
    Flow<i64> f(N + 2);
    for (int i = 0; i < n; i++) {
        f.addEdge(s, i, 0);
    }
    for (int i = 0; i < m; i++) {
        f.addEdge(i + n, t, 0);
    }

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.') {
                f.addEdge(i, j + n, 1);
                cnt++;
            }
        }
    }

    i64 ans = 1LL * cnt * d;

    int sum = 0;
    for (int k = 1; k <= max(n, m); k++) {
        for (auto &i : f.g[s]) {
            f.e[i].cap++;
        }
        for (auto &i : f.g[t]) {
            f.e[i ^ 1].cap++;
        }
        sum += f.maxflow(s, t);
        ans = min(ans, 1LL * c * k + 1LL * d * (cnt - sum));
    }
    cout << ans << '\n';

    return 0;
}
