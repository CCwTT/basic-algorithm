//https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1009
//@@@
//HLD
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=4e5+5;
vector<ll> g[N];
ll a[N];
ll fa[N];
ll dep[N];
ll siz[N];
ll son[N];
ll top[N];
ll dfn[N];
ll ori[N];
ll cnt=0;
ll n,m;

ll mx[N<<2];
ll tag[N<<2];

void init(){
    for(ll i=0;i<N;i++){
        g[i].clear();
    }
    memset(tag,0,sizeof(tag));
    memset(son,0,sizeof(son));
    cnt=0;
}

void dfs1(ll x,ll f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    for(auto y:g[x])if(y!=f){
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
    if(son[x]==0)return;
    dfs2(son[x],tp);
    for(auto y:g[x])if(y!=fa[x]&&y!=son[x]){
        dfs2(y,y);
    }
}

void up(ll p){
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
}

void build(ll p,ll l,ll r){
    if(l==r){
        mx[p]=a[ori[l]];
        return;
    }
    ll m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
    up(p);
}

void modify(ll p,ll l,ll r,ll x,ll v){
    mx[p]=max(mx[p],v);
    if(l==r){
        return;
    }
    ll m=l+r>>1;
    if(x<=m)modify(p<<1,l,m,x,v);
    else modify(p<<1|1,m+1,r,x,v);
}

ll query(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return mx[p];
    }
    ll res=-1;
    ll m=l+r>>1;
    if(x<=m)res=max(res,query(p<<1,l,m,x,y));
    if(y>m)res=max(res,query(p<<1|1,m+1,r,x,y));
    return res;
}

ll path_mx(ll x,ll y){
    ll res=-1;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            res=max(res,query(1,1,n,dfn[top[y]],dfn[y]));
            res=max(res,a[top[y]]+tag[fa[top[y]]]);
            y=fa[top[y]];
        }
        else{
            res=max(res,query(1,1,n,dfn[top[x]],dfn[x]));
            res=max(res,a[top[x]]+tag[fa[top[x]]]);
            x=fa[top[x]];
        }
    }
    res=max(res,query(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y])));
    if(min(dfn[x],dfn[y])==dfn[top[x]]){
        res=max(res,a[top[x]]+tag[fa[top[x]]]);
    }
    return res;
}

void solve(){
    init();

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
    while(m--){
        ll op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            cout<<path_mx(x,y)<<endl;
        }
        else{
            tag[x]+=y;
            if(fa[x]){
                a[fa[x]]+=y;
                modify(1,1,n,dfn[fa[x]],a[fa[x]]);
            }
            if(son[x]){
                a[son[x]]+=y;
                modify(1,1,n,dfn[son[x]],a[son[x]]);
            }
        }
    }
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
       solve(); 
    } 
    return 0;
}