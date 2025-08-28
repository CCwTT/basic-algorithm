//https://ac.nowcoder.com/acm/contest/108306/A
//@@@
//tree dp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=2e5+20,M=25;
ll n,res;
ll ls[N],rs[N];
ll dp[N][M],sz[N];
int init=[](){
    dp[0][1]=1;
    for(ll i=2;i<M;i++)
        dp[0][i]=dp[0][i-1]+dp[0][i-2]+1;
    return 0;
}();

void dfs(ll u){
    if(!u) return;
    dfs(ls[u]);
    dfs(rs[u]);
    sz[u]=sz[ls[u]]+sz[rs[u]]+1;
    dp[u][0]=sz[u];
    dp[u][1]=dp[ls[u]][0]+dp[rs[u]][0];
    for(ll i=2;i<M;i++){
        dp[u][i]=min({
            dp[ls[u]][i-1]+dp[rs[u]][i-1],
            dp[ls[u]][i-1]+dp[rs[u]][i-2],
            dp[ls[u]][i-2]+dp[rs[u]][i-1]
        });
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>ls[i]>>rs[i];
    }
    dfs(1);
    ll res=n;
    for(ll i=0;i<M;i++){
        res=min(res,dp[1][i]);
    }
    cout<<res<<endl;
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