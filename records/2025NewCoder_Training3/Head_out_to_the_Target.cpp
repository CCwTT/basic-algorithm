//https://ac.nowcoder.com/acm/contest/108300/H
//@@@
//HLD
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=1e6+5;
ll n,k;
ll fa[N],top[N],dep[N],siz[N];
ll son[N],dfn[N],ori[N],cnt;
array<ll,3> A[N];
ll t[N];
bool vis[N];
vector<ll> g[N];

void dfs1(ll u){
    dep[u]=dep[fa[u]]+1;
    siz[u]=1;
    for(auto v:g[u]){
        dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

void dfs2(ll u,ll tp){
    top[u]=tp;
    dfn[u]=++cnt;
    ori[cnt]=u;
    if(son[u]) dfs2(son[u],tp);
    for(auto v:g[u]){
        if(v!=son[u]){
            dfs2(v,v);
        }
    }
}

void dfs3(ll u,ll& len){
    if(!t[top[u]]) dfs3(fa[top[u]],len);
    if(len<=0) return;
    ll st=dfn[top[u]]+t[top[u]];
    for(ll i=st;i<=dfn[u]&&len;i++,len--){
        vis[ori[i]]=true;
        t[top[u]]++;
    }
}

void solve(){
    cin>>n>>k;
    for(ll i=2;i<=n;i++){
        cin>>fa[i];
        g[fa[i]].push_back(i);
    }
    for(ll i=1;i<=k;i++){
        for(auto& x:A[i]){
            cin>>x;
        }
    }
    dfs1(1);
    dfs2(1,1);
    t[1]=1;
    vis[1]=true;
    for(ll i=1;i<=k;i++){
        auto [x,l,r]=A[i];
        ll len=r-l+1;
        dfs3(x,len);
        if(vis[x]){
            cout<<max(l,r-len)<<endl;
            return;
        }
    }
    cout<<-1<<endl;
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