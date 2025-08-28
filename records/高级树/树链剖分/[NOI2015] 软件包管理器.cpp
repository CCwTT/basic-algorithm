//https://www.luogu.com.cn/problem/P2146
//@@@
//HLD
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll MAXN=1e5+5;
ll n,m;

vector<ll> g[MAXN];

ll fa[MAXN];
ll dep[MAXN];
ll siz[MAXN];
ll son[MAXN];
ll top[MAXN];
ll dfn[MAXN];
ll cnt=0;

ll sum[MAXN<<2];
bool rst[MAXN<<2];
ll rst_val[MAXN<<2];

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
}

void put_tag(ll p,ll l,ll r,ll v){
    ll n=r-l+1;
    sum[p]=n*v;
    rst[p]=true;
    rst_val[p]=v;
}

void down(ll p,ll l,ll r){
    if(rst[p]){
        ll m=l+r>>1;
        put_tag(p<<1,l,m,rst_val[p]);
        put_tag(p<<1|1,m+1,r,rst_val[p]);
        rst[p]=0;
    }
}

void modify(ll p,ll l,ll r,ll x,ll y,ll v){
    if(x<=l&&r<=y){
        put_tag(p,l,r,v);
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
        return sum[p];
    }
    down(p,l,r);
    ll m=l+r>>1;
    ll res=0;
    if(x<=m) res+=query(p<<1,l,m,x,y);
    if(y>m) res+=query(p<<1|1,m+1,r,x,y);
    return res;
}

void path_rst(ll x,ll v){
    ll y=1;
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

ll install(ll x){
    ll pre=sum[1];
    path_rst(x,1);
    ll post=sum[1];
    return abs(post-pre);
}

ll uninstall(ll x){
    ll pre=sum[1];
    modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,0);
    ll post=sum[1];
    return abs(post-pre);
}

void solve(){
    cin>>n;
    for(ll i=2;i<=n;i++){
        ll f;
        cin>>f;
        f++;
        g[i].push_back(f);
        g[f].push_back(i);
    }
    dfs1(1,0);
    dfs2(1,1);
    cin>>m;
    for(ll i=1;i<=m;i++){
        string op;
        ll x;
        cin>>op>>x;
        x++;
        if(op=="install"){
            cout<<install(x)<<endl;
        }else{
            cout<<uninstall(x)<<endl;
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