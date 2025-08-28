//https://www.luogu.com.cn/problem/P1450
//@@@
//inclusion-exclusion principle
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
ll dp[N];
ll v[4];
ll cnt[4];
ll n,s;

void solve(){
    cin>>v[0]>>v[1]>>v[2]>>v[3];
    dp[0]=1;
    for(ll i=0;i<=3;i++){
        for(ll j=v[i];j<N;j++){
            dp[j]+=dp[j-v[i]];
        }
    }
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>cnt[0]>>cnt[1]>>cnt[2]>>cnt[3]>>s;
        ll illegal=0;
        for(ll mask=1;mask<1<<4;mask++){
            ll t=s;
            ll sign=-1;
            for(ll j=0;j<4;j++){
                if(mask&1<<j){
                    t-=v[j]*(cnt[j]+1);
                    sign=-sign;
                }
            }
            if(t>=0){
                illegal+=sign*dp[t];
            }
        }
        cout<<dp[s]-illegal<<endl;
    }
}



signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}