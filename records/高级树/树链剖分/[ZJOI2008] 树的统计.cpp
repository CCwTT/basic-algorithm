//https://www.luogu.com.cn/problem/P2590
//@@@
//HLD,segment tree
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll MAXN=3e4+5;
ll n,m;
ll a[MAXN];

vector<ll> g[MAXN];

ll fa[MAXN];
ll dep[MAXN];
ll siz[MAXN];
ll son[MAXN];
ll top[MAXN];
ll dfn[MAXN];
ll seg[MAXN];
ll cnt=0;

ll sum[MAXN<<2];
ll mx[MAXN<<2];

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
    seg[cnt]=x;
    if(son[x]==0) return;
    dfs2(son[x],tp);
    for(auto y:g[x]) if(y!=fa[x]){
        if(y!=son[x]){
            dfs2(y,y);
        }
    }
}

void up(ll p){
    sum[p]=sum[p<<1]+sum[p<<1|1];
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
}

void build(ll p,ll l,ll r){
    if(l==r){
        sum[p]=mx[p]=a[seg[l]];
        return;
    }
    ll m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
    up(p);
}

void modify(ll p,ll l,ll r,ll x,ll v){
    if(l==r){
        sum[p]=mx[p]=v;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) modify(p<<1,l,m,x,v);
    else modify(p<<1|1,m+1,r,x,v);
    up(p);
}

ll query_sum(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return sum[p];
    }
    ll m=l+r>>1;
    ll res=0;
    if(x<=m) res+=query_sum(p<<1,l,m,x,y);
    if(y>m) res+=query_sum(p<<1|1,m+1,r,x,y);
    return res;
}

ll query_mx(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return mx[p];
    }
    ll m=l+r>>1;
    ll res=LLONG_MIN/2;
    if(x<=m) res=max(res,query_mx(p<<1,l,m,x,y));
    if(y>m) res=max(res,query_mx(p<<1|1,m+1,r,x,y));
    return res;
}

ll path_sum(ll x,ll y){
    ll res=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            res+=query_sum(1,1,n,dfn[top[y]],dfn[y]);
            y=fa[top[y]];
        }else{
            res+=query_sum(1,1,n,dfn[top[x]],dfn[x]);
            x=fa[top[x]];
        }
    }
    res+=query_sum(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]));
    return res;
}

ll path_mx(ll x,ll y){
    ll res=LLONG_MIN/2;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            res=max(res,query_mx(1,1,n,dfn[top[y]],dfn[y]));
            y=fa[top[y]];
        }else{
            res=max(res,query_mx(1,1,n,dfn[top[x]],dfn[x]));
            x=fa[top[x]];
        }
    }
    return max(res,query_mx(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y])));
}

void solve(){
    cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    cin>>m;
    for(ll i=1;i<=m;i++){
        string op;
        ll x,y;
        cin>>op>>x>>y;
        if(op=="CHANGE"){
            modify(1,1,n,dfn[x],y);
        }else if(op=="QMAX"){
            cout<<path_mx(x,y)<<endl;
        }else{
            cout<<path_sum(x,y)<<endl;
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

