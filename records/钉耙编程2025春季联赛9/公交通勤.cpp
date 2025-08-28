//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1001
//@@@
//multi-dimensional dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll t,n,m;
    cin>>t>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n-1;++i){
        cin>>a[i];
    }
    vector<vector<vector<ll>>> f(n*t+1,vector<vector<ll>>(n+1,vector<ll>(m+1,LLONG_MAX/2)));
    f[0][0][0]=0;
    for(ll i=0;i<=n*t;++i) for(ll prev=0;prev<=i;prev++){
        for(ll j=1;j<=n-1;j++){
            ll hyp=abs(a[j]-i);
            ll delta=(i-prev)*(i-prev);
            if(j==n-1) delta+=(n*t-i)*(n*t-i);
            for(ll k=hyp;k<=m;k++){
                f[i][j][k]=min(f[i][j][k],f[prev][j-1][k-hyp]+delta);
            }
        }
    }
    ll ans=LLONG_MAX/2;
    for(ll i=0;i<=n*t;i++){
        for(ll k=0;k<=m;k++){
            ans=min(ans,f[i][n-1][k]);
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}