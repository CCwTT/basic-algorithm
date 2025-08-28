//https://www.luogu.com.cn/problem/P2486
//@@@
//HLD,segment tree
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

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

struct node{
    ll sum;
    ll lcolor;
    ll rcolor;
    ll rst;
};
node tr[MAXN<<2];

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
    tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
    if(tr[p<<1].rcolor==tr[p<<1|1].lcolor){
        tr[p].sum--;
    }
    tr[p].lcolor=tr[p<<1].lcolor;
    tr[p].rcolor=tr[p<<1|1].rcolor;
}

void put_tag(ll p,ll v){
    tr[p].sum=1;
    tr[p].lcolor=tr[p].rcolor=v;
    tr[p].rst=v;
}

void down(ll p,ll l,ll r){
    if(tr[p].rst){
        put_tag(p<<1,tr[p].rst);
        put_tag(p<<1|1,tr[p].rst);
        tr[p].rst=0;
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        tr[p].sum=1;
        tr[p].lcolor=tr[p].rcolor=a[ori[l]];
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
    down(p,l,r);
    ll m=l+r>>1;
    if(x<=m) modify(p<<1,l,m,x,y,v);
    if(y>m) modify(p<<1|1,m+1,r,x,y,v);
    up(p);
}

ll query(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return tr[p].sum;
    }
    down(p,l,r);
    ll m=l+r>>1;
    if(y<=m) return query(p<<1,l,m,x,y);
    else if(x>m) return query(p<<1|1,m+1,r,x,y); 
    else{
        ll res=query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
        if(tr[p<<1].rcolor==tr[p<<1|1].lcolor){
            res--;
        }
        return res;
    }
}

ll query_color(ll p,ll l,ll r,ll x){
    if(l==r){
        return tr[p].lcolor;
    }
    down(p,l,r);
    ll m=l+r>>1;
    if(x<=m) return query_color(p<<1,l,m,x);
    else return query_color(p<<1|1,m+1,r,x);
}

void path_modify(ll x,ll y,ll v){
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
}

ll path_colors(ll x,ll y){
    ll res=0;
    ll sonc,fac;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            res+=query(1,1,n,dfn[top[y]],dfn[y]);
            sonc=query_color(1,1,n,dfn[top[y]]);
            fac=query_color(1,1,n,dfn[fa[top[y]]]);
            y=fa[top[y]];
        }else{
            res+=query(1,1,n,dfn[top[x]],dfn[x]);
            sonc=query_color(1,1,n,dfn[top[x]]);
            fac=query_color(1,1,n,dfn[fa[top[x]]]);
            x=fa[top[x]];
        }
        if(sonc==fac){
            res--;
        }
    }
    res+=query(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]));
    return res;
}

void solve(){
    cin>>n>>m;
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
    for(ll i=1;i<=m;i++){
        char op;
        ll x,y,z;
        cin>>op>>x>>y;
        if(op=='C'){
            cin>>z;
            path_modify(x,y,z);
        }else{
            cout<<path_colors(x,y)<<endl;
        }
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