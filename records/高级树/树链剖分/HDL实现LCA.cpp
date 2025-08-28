//https://www.luogu.com.cn/problem/P3379
//@@@
//HLD,lca
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll N=5e5+5;
ll n,m;

vector<ll> g[N]; ll root;
ll dep[N],pa[N],siz[N],son[N],top[N]; //dpsst

void dfs1(ll u,ll fa){
    dep[u]=dep[fa]+1;
    pa[u]=fa;
    siz[u]=1;
    for(auto v:g[u]) if(v!=fa){
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]){
            son[u]=v;
        }
    }
}

void dfs2(ll u,ll tp){
    top[u]=tp;
    for(auto& v:g[u]) if(v!=pa[u]){
        if(v==son[u]){
            dfs2(v,tp);
        }else{
            dfs2(v,v);
        }
    }
}

ll lca(ll u,ll v){
    while(top[u]!=top[v]){
        if(dep[top[u]]>=dep[top[v]]){
            u=pa[top[u]];
        }else{
            v=pa[top[v]];
        }
    }
    return dep[u]<=dep[v]?u:v;
}

void solve(){
    cin>>n>>m>>root;
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(root,0);
    dfs2(root,root);
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}