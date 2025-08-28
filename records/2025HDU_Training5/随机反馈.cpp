//https://acm.hdu.edu.cn/contest/view-code?cid=1176&rid=4773
//@@@
//expectation dp
//E(此)=p*(E(后)+inc)+(1-p)*est
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
ll n,p[N];
long double dp[N];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>p[i];
    }
    dp[n]=n;
    for(ll i=n-1;i;i--){
        dp[i]=min(dp[i+1],p[i]/1000.0*(dp[i+1]+20)+(1000-p[i])/1000.0*i);
    }
    cout<<fixed<<setprecision(10)<<dp[1]<<endl;
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