#include <bits/stdc++.h>
#define ll long long
#define int long long
#define endl '\n'

using namespace std;
using vi= vector<int>;
using vvi= vector<vi>;
using pii= pair<int, int>;

constexpr int N= 5e5 + 10;
vi factor[N];
int a[N];
int sum1[N], sum2[N];
int add1[N], add2[N];
int n, m;

int init= [] {
    for(int i= 1; i <= 500000; i++) {
        for(int j= 1; j * j <= i; j++) {
            if(i % j == 0) {
                if(j * j == i)
                    factor[i].push_back(j);
                else {
                    factor[i].push_back(j);
                    factor[i].push_back(i / j);
                }
            }
        }
    }
    // for (int i = 1; i <= 10; i++) {
    // 	cout << "factors of " << i << ":";
    // 	for (auto j: factor[i]) {
    // 		cout << j << " ";
    // 	}
    // 	cout << endl;
    // }
    return 0;
}();

void solve() {
    cin >> n >> m;
    for(int i= 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i= 1; i <= n; i++) {
        for(int j= i; j <= n; j+= i) {
            sum1[i]+= a[j];
        }
        for(auto j: factor[i]) {
            sum2[i]+= a[j];
        }
        // cout << i << ":" << sum1[i] << " " << sum2[i] << endl;
    }
    while(m--) {
        int op, x, k;
        cin >> op;
        if(op == 1) {
            cin >> x >> k;
            if(x <= 750) {
                add1[x]+= k;
            } else {
                for(int i= x; i <= n; i+= x) {
                    sum1[i]+= k * (n / i);
                }
            }
            for(auto j: factor[x]) {
                sum1[j]+= k * (n / x);
            }
        } else if(op == 2) {//
            cin >> x >> k;
            for(auto i: factor[x]) {
                sum2[i]+= k * factor[i].size();
            }
            if(x <= 750) {
                add2[x]+= k;
            } else {
                for(int j= x; j <= n; j+=x) {
                    sum2[x]+= k * factor[x].size();
                }
            }
        } else if(op == 3) {
            cin >> x;
            int ans= sum1[x];
            for(int i= 1; i <= min(x, 750ll); i++) {
                
                if(x % i == 0) {
                    ans+= add1[i] * (n / x);
                }
            }
            cout << ans << endl;
        } else {
            cin >> x;
            int ans= sum2[x];
            for(int i= 1; i <= min(x, 750ll); i++) {
                if(x % i == 0) {
                    ans+= add2[i] * factor[i].size();
                }
            }
            cout << ans << endl;
        }
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t= 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
