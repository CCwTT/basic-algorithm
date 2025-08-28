//https://loj.ac/p/515
//@@@
//bitset-optimized dp
//原始dp:O(n^5) bitset优化:O(n^2)
//优化掉了枚举值域的时间复杂度O(n^3)
//将加法操作转化为bitset权值空间上的左移操作
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=105;
ll n,a[N],b[N];
bitset<N*N*N> f[N];

void solve() {
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    f[0][0]=1;
    for(ll i=1;i<=n;i++){
        for(ll j=a[i];j<=b[i];j++){
            f[i]|=f[i-1]<<(j*j);
        }
    }
    cout<<f[n].count()<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}