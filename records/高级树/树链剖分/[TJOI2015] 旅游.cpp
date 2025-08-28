//https://www.luogu.com.cn/problem/P3976
//@@@
//HLD,segment tree
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf LLONG_MAX/2
typedef long long ll;

const ll MAXN=1e5+5;
ll n,m;

ll a[MAXN];

vector<ll> g[MAXN];

ll fa[MAXN];
ll dep[MAXN];
ll siz[MAXN];
ll son[MAXN];
ll top[MAXN];
ll dfn[MAXN];
ll ori[MAXN];
ll cnt=0;

ll mx[MAXN<<2];
ll mn[MAXN<<2];
ll lprofit[MAXN<<2];
ll rprofit[MAXN<<2];
ll add[MAXN<<2];

void dfs1(ll x,ll f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    for(auto y:g[x]) if(y!=f){
        dfs1(y,x);
        siz[x]+=siz[y];
        if(son[x]==0||siz[son[x]]<siz[y]){
            son[x]=y;
        }
    }
}

void dfs2(ll x,ll tp){
    top[x]=tp;
    dfn[x]=++cnt;
    ori[cnt]=x;
    if(son[x]==0) return;
    dfs2(son[x],tp);
    for(auto y:g[x]) if(y!=fa[x]){
        if(y!=son[x]){
            dfs2(y,y);
        }
    }
}

void up(ll p){
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
    mn[p]=min(mn[p<<1],mn[p<<1|1]);
    lprofit[p]=max({lprofit[p<<1],lprofit[p<<1|1],mx[p<<1|1]-mn[p<<1]});
    rprofit[p]=max({rprofit[p<<1],rprofit[p<<1|1],mx[p<<1]-mn[p<<1|1]});
}

void put_tag(ll p,ll v){
    mx[p]+=v;
    mn[p]+=v;
    add[p]+=v;
}

void down(ll p){
    if(add[p]){
        put_tag(p<<1,add[p]);
        put_tag(p<<1|1,add[p]);
        add[p]=0;
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        mx[p]=mn[p]=a[ori[l]];
        return;
    }
    ll m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
    up(p);
}

void modify(ll p,ll l,ll r,ll x,ll y,ll v){
    if(x<=l&&r<=y){
        put_tag(p,v);
        return;
    }
    down(p);
    ll m=l+r>>1;
    if(x<=m) modify(p<<1,l,m,x,y,v);
    if(y>m) modify(p<<1|1,m+1,r,x,y,v);
    up(p);
}

tuple<ll,ll,ll,ll> info;
void merge(ll rmx,ll rmn,ll rlprofit,ll rrprofit){
    auto [lmx,lmn,llprofit,lrprofit]=info;
    info={
        max(lmx,rmx),
        min(lmn,rmn),
        max({llprofit,rlprofit,rmx-lmn}),
        max({lrprofit,rrprofit,lmx-rmn})
    };
}

void query(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        merge(mx[p],mn[p],lprofit[p],rprofit[p]);
        return;
    }
    down(p);
    ll m=l+r>>1;
    if(x<=m) query(p<<1,l,m,x,y);
    if(y>m) query(p<<1|1,m+1,r,x,y);
}

void query(ll x,ll y){
    info={-inf,inf,0,0};
    query(1,1,n,x,y);
}

ll compute(ll x,ll y,ll v){
    ll x0=x,y0=y;
    tuple<ll,ll,ll,ll> xpath={-inf,inf,0,0};
    tuple<ll,ll,ll,ll> ypath={-inf,inf,0,0};
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            query(dfn[top[y]],dfn[y]);
            auto [y1,y2,y3,y4]=ypath;
            merge(y1,y2,y3,y4);
            ypath=info;
            y=fa[top[y]];
        }else{
            query(dfn[top[x]],dfn[x]);
            auto [x1,x2,x3,x4]=xpath;
            merge(x1,x2,x3,x4);
            xpath=info;
            x=fa[top[x]];
        }
    }
    if(dep[x]<=dep[y]){
        query(dfn[x],dfn[y]);
        auto [y1,y2,y3,y4]=ypath;
        merge(y1,y2,y3,y4);
        ypath=info;
    }else{
        query(dfn[y],dfn[x]);
        auto [x1,x2,x3,x4]=xpath;
        merge(x1,x2,x3,x4);
        xpath=info;
    }
    ll res=max({get<3>(xpath),get<2>(ypath),get<0>(ypath)-get<1>(xpath)});
    x=x0,y=y0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            modify(1,1,n,dfn[top[y]],dfn[y],v);
            y=fa[top[y]];
        }else{
            modify(1,1,n,dfn[top[x]],dfn[x],v);
            x=fa[top[x]];
        }
    }
    modify(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),v);
    return res;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    cin>>m;
    for(ll i=1;i<=m;i++){
        ll x,y,v;
        cin>>x>>y>>v;
        cout<<compute(x,y,v)<<endl;
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