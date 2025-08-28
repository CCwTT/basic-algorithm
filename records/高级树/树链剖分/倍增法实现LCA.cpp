//https://www.luogu.com.cn/problem/P3379
//@@@
//binary lifting,lca
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll N=5e5+5;
const ll H=19;
ll n,m;

vector<ll> g[N]; ll root;
ll stj[N][H],dep[N];

void dfs(ll u,ll fa){
    dep[u]=dep[fa]+1;
    stj[u][0]=fa;
    for(ll d=1;d<H;d++){
        stj[u][d]=stj[stj[u][d-1]][d-1];
    }
    for(auto& v:g[u]) if(v!=fa){
        dfs(v,u);
    }
}

ll lca(ll u,ll v){
    if(dep[u]<dep[v]) swap(u,v);
    for(ll d=H-1;d>=0;d--){
        if(dep[stj[u][d]]>=dep[v]){
            u=stj[u][d];
        }
    }
    if(u==v) return u;
    for(ll d=H-1;d>=0;d--){
        if(stj[u][d]!=stj[v][d]){
            u=stj[u][d];
            v=stj[v][d];
        }
    }
    return stj[u][0];
}

void solve(){
    cin>>n>>m>>root;
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(root,0);
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