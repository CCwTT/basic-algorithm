//https://codeforces.com/problemset/problem/803/F
//@@@
//inclusion-exclusion principle(dp)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll mod=1e9+7;
const ll N=1e5+5;

ll dp[N];
ll cnt[N];
ll pw2[N];
ll n;

ll init=[]{
    pw2[0]=1;
    for(ll i=1;i<N;i++){
        pw2[i]=pw2[i-1]*2%mod;
    }
    return 0;
}();

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        ll x;
        cin>>x;
        cnt[x]++;
    }
    for(ll i=N-1;i>=1;i--){
        ll sum=0;
        for(ll j=i;j<N;j+=i){
            sum+=cnt[j];
        }
        dp[i]=(pw2[sum]-1+mod)%mod;
        for(ll j=i*2;j<N;j+=i){
            dp[i]=(dp[i]-dp[j]+mod)%mod;
        }
    }
    cout<<dp[1]<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}