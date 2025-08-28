#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll MAXN=300010;
ll n,k;
ll a[MAXN],b[MAXN];
ll dp[MAXN][11][11];

ll dfs(ll p,ll k1,ll k2){
    if(p==2*n+1) return 0;
    if(dp[p][k1][k2]!=LLONG_MIN/2) return dp[p][k1][k2];
    ll& res=dp[p][k1][k2];
    if(p&1){
        if(k1+1<=k){
            return res=max(
                dfs(p+1,k1,k2),
                dfs(p+1,k1+1,k2)+a[(p-1)/2+k1-k2+1]
            );
        }else{
            return res=dfs(p+1,k1,k2);
        }
    }else{
        if(k2+1<=k){
            return res=min(
                dfs(p+1,k1,k2),
                dfs(p+1,k1,k2+1)-b[p/2+k2-k1+1]
            );
        }else{
            return res=dfs(p+1,k1,k2);
        }
    }
}

void solve(){
    cin>>n>>k;
    for(ll i=1;i<=n;i++) cin>>a[i];
    for(ll i=1;i<=n;i++) cin>>b[i];
    sort(a+1,a+n+1,greater<ll>());
    sort(b+1,b+n+1,greater<ll>());
    for(ll i=0;i<MAXN;i++){
        for(ll j=0;j<11;j++){
            for(ll k=0;k<11;k++){
                dp[i][j][k]=LLONG_MIN/2;
            }
        }
    }
    cout<<dfs(1,0,0)<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--) solve();
    return 0;
}