//https://www.luogu.com.cn/problem/P2607
//@@@
//functional graph
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e6+5;
vector<ll> rg[N];
ll n;
ll a[N];
bool vis[N];
ll rt1,rt2;
ll dp[N][2];

void dfs1(ll u,ll rt){
    vis[u]=true;
    for(auto v:rg[u]){
        if(v==rt){
            rt1=u;
            rt2=v;
            return;
        }
        if(vis[v]) continue;
        dfs1(v,rt);
    }
}

ll dfs2(ll u,ll rt){
    dp[u][0]=0,dp[u][1]=a[u];
    for(auto v:rg[u]) if(v!=rt){
        dfs2(v,rt);
        dp[u][0]+=max(dp[v][0],dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
    return dp[u][0];
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        ll j;
        cin>>j;
        rg[j].push_back(i);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            rt1=rt2=0;
            dfs1(i,i);
            ans+=max(dfs2(rt1,rt1),dfs2(rt2,rt2));
        }
    }
    cout<<ans<<endl;
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