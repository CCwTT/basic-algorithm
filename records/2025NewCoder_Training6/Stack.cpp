//https://ac.nowcoder.com/acm/contest/108303/C
//@@@
//brain teaser
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5e5+5;
const ll mod=998244353;
ll n;
ll dp0[N];
ll dp1[N];
ll dp2[N];
ll dp3[N];

int init=[]{
    dp0[1]=1;
    for(ll i=2;i<N;i++){
        dp0[i]=dp0[i-1]*i%mod;
    }
    dp1[1]=1;
    for(ll i=2;i<N;i++){
        dp1[i]=(dp1[i-1]*(i-1)+dp1[i-1]+dp0[i-1])%mod;
    }
    dp2[1]=1;
    for(ll i=2;i<N;i++){
        dp2[i]=(dp2[i-1]*(i-1)+dp2[i-1]+2*dp1[i-1]+dp0[i-1])%mod;
    }
    dp3[1]=1;
    for(ll i=2;i<N;i++){
        dp3[i]=(dp3[i-1]*(i-1)+dp3[i-1]+3*dp2[i-1]+3*dp1[i-1]+dp0[i-1])%mod;
    }
    return 0;
}();

void solve(){
    cin>>n;
    cout<<dp3[n]<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}