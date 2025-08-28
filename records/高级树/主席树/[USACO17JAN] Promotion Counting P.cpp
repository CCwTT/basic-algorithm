//https://www.luogu.com.cn/problem/P3605
//@@@
//persistent segment tree on tree
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

class discretizer{
public:
    vector<ll> disc;
    discretizer(){
        disc.push_back(LLONG_MIN);
    }

    void insert(ll x){
        disc.push_back(x);
    }

    ll discretize(){
        sort(disc.begin(),disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size()-1;
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
};
discretizer disc;

const ll MAXN=1e5+5;
const ll MAXT=MAXN*30;
ll a[MAXN];
ll root[MAXN];
ll dfn[MAXN];
ll di=0;
struct node{
    ll sz;
    ll lc,rc;
};
node tr[MAXT];
ll cnt=0;

vector<ll> g[MAXN];
ll sz[MAXN];

ll n,N;
ll l,r,ans;

void up(ll p){
    tr[p].sz=tr[tr[p].lc].sz+tr[tr[p].rc].sz;
}

void build(ll& p,ll l,ll r){
    p=++cnt;
    if(l==r){
        tr[p].sz=0;
        return;
    }
    ll m=(l+r)>>1;
    build(tr[p].lc,l,m);
    build(tr[p].rc,m+1,r);
    up(p);
}

void update(ll& p,ll l,ll r,ll pre,ll x,ll v=1){
    p=++cnt,tr[p]=tr[pre];
    if(l==r){
        tr[p].sz++;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x);
    up(p);
}

ll query(ll p,ll q,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return tr[q].sz-tr[p].sz;
    }
    ll res=0;
    ll m=l+r>>1;
    if(x<=m) res+=query(tr[p].lc,tr[q].lc,l,m,x,y);
    if(y>m) res+=query(tr[p].rc,tr[q].rc,m+1,r,x,y);
    return res;
}

void dfs(ll x,ll fa){
    dfn[x]=++di;
    sz[x]=1;
    for(auto y:g[x]) if(y!=fa){
        dfs(y,x);
        sz[x]+=sz[y];
    }
}

void dfs2(ll x,ll fa){
    update(root[dfn[x]],1,N,root[dfn[x]-1],a[x]);
    for(auto y:g[x]) if(y!=fa){
        dfs2(y,x);
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        disc.insert(a[i]);
    }
    N=disc.discretize();
    for(ll i=1;i<=n;i++){
        a[i]=disc.query(a[i]);
    }
    build(root[0],1,N);
    for(ll i=2;i<=n;i++){
        ll f;
        cin>>f;
        g[f].push_back(i);
        g[i].push_back(f);
    }
    dfs(1,0);
    dfs2(1,0);
    for(ll i=1;i<=n;i++){
        cout<<sz[i]-query(root[dfn[i]-1],root[dfn[i]+sz[i]-1],1,N,1,a[i])<<endl;
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
