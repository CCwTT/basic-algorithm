//https://www.luogu.com.cn/problem/P3387
//@@@
//tarjan-scc
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
ll n,m;
ll a[N],b[N];
vector<ll> g[N],G[N];
ll dfn[N],low[N];
stack<ll> stk;
bool ins[N];
ll scc[N],siz[N];
ll dp[N];
ll tim=0,cnt=0;

void tarjan(ll x){
    dfn[x]=low[x]=++tim;
    ins[x]=true;
    stk.push(x);
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(ins[y]){
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        ++cnt;
        while(true){
            ll u=stk.top();
            stk.pop();
            ins[u]=0;
            scc[u]=cnt;
            siz[cnt]++;
            if(u==x) break;
        }
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(ll i=1;i<=n;i++){
        b[scc[i]]+=a[i];
        for(auto j:g[i]){
            if(scc[i]!=scc[j]){
                G[scc[i]].push_back(scc[j]);
            }
        }
    }
    for(ll i=cnt;i>=1;i--){
        if(dp[i]==0){
            dp[i]=b[i];
        }
        for(auto j:G[i]){
            dp[j]=max(dp[j],dp[i]+b[j]);
        }
    }
    ll ans=0;
    for(ll i=1;i<=cnt;i++){
        ans=max(ans,dp[i]);
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