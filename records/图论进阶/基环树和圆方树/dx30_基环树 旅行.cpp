//https://www.luogu.com.cn/problem/P5022
//@@@
//functional graph
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5005;
ll n,m;
set<ll> g[N];
pair<ll,ll> edges[N];
ll sp1,sp2;
bool vis[N];
vector<ll> path(N,inf);
ll cntp=0;
bool better=false;

//return true represents shortcut
bool dfs(ll u){
    if(!better){
        if(u>path[cntp+1]) return true;
        if(u<path[cntp+1]) better=true;
    }
    vis[u]=true;
    path[++cntp]=u;
    for(auto v:g[u]){
        if(vis[v]) continue;
        if(u==sp1&&v==sp2) continue;
        if(u==sp2&&v==sp1) continue;
        if(dfs(v)) return true;
    }
    return false;
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].insert(v);
        g[v].insert(u);
        edges[i]={u,v};
    }
    if(m==n-1){
        dfs(1);
    }else{
        for(ll i=1;i<=m;i++){
            tie(sp1,sp2)=edges[i];
            memset(vis,0,sizeof(vis));
            cntp=0;
            better=false;
            dfs(1);
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<path[i]<<" ";
    }
    cout<<endl;
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