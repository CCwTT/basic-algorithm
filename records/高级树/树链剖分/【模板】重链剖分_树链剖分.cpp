//https://www.luogu.com.cn/problem/P3384
//@@@
//HLD
//subtree operation:O(logn)
//path operation:O(log^2n) 
//Proof method is analogous to heuristic merging
// Theorem: Any path in a tree can be split into O(log n) consecutive intervals.
// Proof
// 1.Since heavy chains are all consecutive in the transformed sequence, this theorem is equivalent to the statement that any path in a tree passes through no more than O(log n) heavy chains.
// 2.Consider the worst-case scenario, where the path only traverses light edges and all heavy chains are individually formed by light children.
// 3.For the current node, since it has a light child, it must have a heavy child. If the size of the subtree rooted at the light child is x, the size of the subtree rooted at the current node must be at least 2x.
// 4.Thus, each traversal of a light edge doubles the subtree size. Given that the total number of nodes in the tree is n, the maximum number of light edges that can be traversed is O(log n).
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll MAXN=1e5+5;
ll n,m,root,mod;
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

ll sum[MAXN<<2];
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
    sum[p]=(sum[p<<1]+sum[p<<1|1])%mod;
}

void put_tag(ll p,ll l,ll r,ll v){
    ll n=r-l+1;
    sum[p]=(sum[p]+n*v)%mod;
    add[p]=(add[p]+v)%mod;
}

void down(ll p,ll l,ll r){
    if(add[p]){
        ll m=l+r>>1;
        put_tag(p<<1,l,m,add[p]);
        put_tag(p<<1|1,m+1,r,add[p]);
        add[p]=0;
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        sum[p]=a[ori[l]]%mod;
        return;
    }
    ll m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
    up(p);
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
    if(x<=m) res=(res+query(p<<1,l,m,x,y))%mod;
    if(y>m) res=(res+query(p<<1|1,m+1,r,x,y))%mod;
    return res;
}

void path_add(ll x,ll y,ll v){
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

void subtree_add(ll x,ll v){
    modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,v);
}

ll path_sum(ll x,ll y){
    ll res=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            res=(res+query(1,1,n,dfn[top[y]],dfn[y]))%mod;
            y=fa[top[y]];
        }else{
            res=(res+query(1,1,n,dfn[top[x]],dfn[x]))%mod;
            x=fa[top[x]];
        }
    }
    res=(res+query(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y])))%mod;
    return res;
}

// 计算节点x的子树和
ll subtree_sum(ll x){
    // 查询节点x的子树和
    return query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
}

void solve(){
    cin>>n>>m>>root>>mod;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(root,0);
    dfs2(root,root);
    build(1,1,n);
    for(ll i=1;i<=m;i++){
        ll op,x,y,v;
        cin>>op;
        if(op==1){
            cin>>x>>y>>v;
            path_add(x,y,v);
        }else if(op==2){
            cin>>x>>y;
            cout<<path_sum(x,y)<<endl;
        }else if(op==3){
            cin>>x>>v;
            subtree_add(x,v);
        }else{
            cin>>x;
            cout<<subtree_sum(x)<<endl;
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

