//https://www.luogu.com.cn/problem/P5236
//@@@
//round-square tree
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e4,M=N*3;
ll n,m,Q;
ll cnt;

struct edge{
    ll to,w,ne;
}e[M];
ll h1[N],h2[N],cnte=1;  //graph
ll fa[N],fe[N],fw[N];   //info
ll s[N],sc[N]; //circle

ll dfn[N],low[N],tim;  //tarjan
ll stj[N][14],dep[N],d[N]; //lca

ll A,B;

void add_edge(ll* h,ll u,ll v,ll w){
    e[++cnte]={v,w,h[u]};
    h[u]=cnte;
}

void build_tree(ll bg,ll ed,ll w_st){
    ll sum=w_st;
    for(ll p=ed;p!=bg;p=fa[p]){
        s[p]=sum;
        sum+=fw[p];
    }
    add_edge(h2,bg,++cnt,0);
    for(ll p=ed;p!=bg;p=fa[p]){
        sc[p]=sum;
        add_edge(h2,cnt,p,min(s[p],sum-s[p]));
    }
}

void tarjan(ll u,ll ine){ //tarjan for bridge
    dfn[u]=low[u]=++tim;
    for(ll i=h1[u];i;i=e[i].ne){
        auto [v,w,ne]=e[i];
        if(!dfn[v]){
            fa[v]=u,fe[v]=i,fw[v]=w;
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){ //non-loop edge
                add_edge(h2,u,v,w); 
            }
        }else if(i!=(ine^1)){ //loop edge
            low[u]=min(low[u],dfn[v]);
        }
    }
    for(ll i=h1[u];i;i=e[i].ne){
        auto [v,w,ne]=e[i];
        if(dfn[u]<dfn[v]&&fe[v]!=i){
            build_tree(u,v,w);
        }
    }
}

void dfs(ll u,ll f){
    dep[u]=dep[f]+1;
    stj[u][0]=f;
    for(ll d=1;d<14;d++){
        stj[u][d]=stj[stj[u][d-1]][d-1];
    }
    for(ll i=h2[u];i;i=e[i].ne){
        auto [v,w,ne]=e[i];
        d[v]=d[u]+w;
        dfs(v,u);
    }
}

ll lca(ll u,ll v){
    if(dep[u]<dep[v]) swap(u,v);
    for(ll d=13;d>=0;d--){
        if(dep[stj[u][d]]>=dep[v]){
            u=stj[u][d];
        }
    }
    if(u==v) return u;
    for(ll d=13;d>=0;d--){
        if(stj[u][d]!=stj[v][d]){
            u=stj[u][d];
            v=stj[v][d];
        }
    }
    A=u,B=v;
    return stj[u][0];
}

void solve(){
    cin>>n>>m>>Q;
    cnt=n;
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        add_edge(h1,u,v,w);
        add_edge(h1,v,u,w);
    }
    tarjan(1,0);
    dfs(1,0);
    while(Q--){
        ll u,v;
        cin>>u>>v;
        ll z=lca(u,v);
        if(z<=n){ //z is round point
            cout<<d[u]+d[v]-2*d[z]<<endl;
        }else{ //z is square point
            ll len=abs(s[A]-s[B]);
            len=min(len,sc[A]-len);
            cout<<len+d[u]-d[A]+d[v]-d[B]<<endl;
        }
    }
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