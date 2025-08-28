#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=4e5+10;
ll n,p[N];
vector<ll> g[N];

ll dep[N],pa[N],siz[N],son[N],top[N];
void dfs1(ll u,ll fa){
    dep[u]=dep[fa]+1;
    pa[u]=fa;
    siz[u]=1;
    son[u]=0;
    for(auto& v:g[u]) if(v!=fa){
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
            dfs2(son[u],tp);
        }else{
            dfs2(v,v);
        }
    }
}

ll __lca(ll u,ll v){
    while(top[u]!=top[v]){
        if(dep[top[u]]>dep[top[v]]){
            u=pa[top[u]];
        }else{
            v=pa[top[v]];
        }
    }
    return dep[u]<=dep[v]?u:v;
}

ll dis(ll u,ll v){
    ll x=__lca(u,v);
    return dep[u]+dep[v]-2*dep[x];
}

void clear(){
    for(ll i=1;i<=n;i++){
        g[i].clear();
        dep[i]=pa[i]=siz[i]=son[i]=top[i]=0;
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        ll w;
        cin>>w;
        w++;
        p[w]=i;
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs1(1,0);
    dfs2(1,1);
    
    cout<<0<<endl;
    ll s=p[1];
    ll t=p[2];

    cout<<(dis(s,t)+1)/2<<endl;
    
    for(ll i=3;i<=n;i++){
        ll x=p[i];
        if(dis(x,s)<=dis(x,t)){
            if(dis(x,t)>dis(s,t)){
                s=x;
            }
        }else{
            if(dis(s,x)>dis(s,t)){
                t=x;
            }
        }
        cout<<(dis(s,t)+1)/2<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}