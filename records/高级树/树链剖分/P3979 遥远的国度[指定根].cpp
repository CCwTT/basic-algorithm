//https://www.luogu.com.cn/problem/P3979
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

ll mn[MAXN<<2];
ll rst[MAXN<<2];

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
    mn[p]=min(mn[p<<1],mn[p<<1|1]);
}

void put_tag(ll p,ll v){
    mn[p]=v;
    rst[p]=v;
}

void down(ll p){
    if(rst[p]){
        put_tag(p<<1,rst[p]);
        put_tag(p<<1|1,rst[p]);
        rst[p]=0;
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        mn[p]=a[ori[l]];
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

ll query(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return mn[p];
    }
    down(p);
    ll m=l+r>>1;
    ll res=inf;
    if(x<=m) res=min(res,query(p<<1,l,m,x,y));
    if(y>m) res=min(res,query(p<<1|1,m+1,r,x,y));
    return res;
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

//It is guaranteed that the root is in the subtree of x
ll find_son(ll root,ll x){
    while(top[root]!=top[x]){
        if(fa[top[root]]==x){
            return top[root];
        }
        root=fa[top[root]];
    }
    return son[x];
}

ll tree_query(ll root,ll x){
    if(root==x){
        return mn[1];
    }
    if(dfn[root]<dfn[x]||dfn[x]+siz[x]-1<dfn[root]){
        return query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
    }
    ll xson=find_son(root,x);
    ll res=inf;
    //dispense with [dfn[xson],dfn[xson]+siz[xson]-1]
    if(1<=dfn[xson]-1){
        res=min(res,query(1,1,n,1,dfn[xson]-1));
    }
    if(dfn[xson]+siz[xson]<=n){
        res=min(res,query(1,1,n,dfn[xson]+siz[xson],n));
    }
    return res;
}

void solve(){
    cin>>n>>m;
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
    ll root;
    cin>>root;
    for(ll i=1;i<=m;i++){
        ll op,x,y,v;
        cin>>op;
        if(op==1){
            cin>>root;
        }else if(op==2){
            cin>>x>>y>>v;
            path_modify(x,y,v);
        }else{
            cin>>x;
            cout<<tree_query(root,x)<<endl;
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