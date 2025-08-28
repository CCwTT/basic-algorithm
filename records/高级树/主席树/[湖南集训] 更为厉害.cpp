//https://www.luogu.com.cn/problem/P3899
//@@@
//persistent segment tree,dfn
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

const ll MAXN=3e5+5;
const ll MAXT=MAXN*50;
ll n,m,depth;

vector<ll> g[MAXN];
ll deep[MAXN];
ll sz[MAXN];
int dfn[MAXN];

int root[MAXN];
int lc[MAXT];
int rc[MAXT];
ll sum[MAXT];
ll cnt=0;

ll clone(ll p){
    ll q=++cnt;
    lc[q]=lc[p];
    rc[q]=rc[p];
    sum[q]=sum[p];
    return q;
}

void up(ll p){
    sum[p]=sum[lc[p]]+sum[rc[p]];
}

ll build(ll l,ll r){
    ll p=++cnt;
    if(l==r){
        sum[p]=0;
    }else{
        ll m=l+r>>1;
        lc[p]=build(l,m);
        rc[p]=build(m+1,r);
        up(p);
    }
    return p;
}

ll update(ll p,ll l,ll r,ll x,ll v){
    p=clone(p);
    if(l==r){
        sum[p]+=v;
    }else{
        ll m=l+r>>1;
        if(x<=m) lc[p]=update(lc[p],l,m,x,v);
        if(x>m) rc[p]=update(rc[p],m+1,r,x,v);
        up(p);
    }
    return p;
}

ll query(ll u,ll v,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        return sum[v]-sum[u];
    }
    ll res=0;
    ll m=l+r>>1;
    if(x<=m) res+=query(lc[u],lc[v],l,m,x,y);
    if(y>m) res+=query(rc[u],rc[v],m+1,r,x,y);
    return res;
}

ll cntd=0;
void dfs1(ll x,ll fa){
    deep[x]=deep[fa]+1;
    depth=max(depth,deep[x]);
    sz[x]=1;
    dfn[x]=++cntd;
    for(auto y:g[x]) if(y!=fa){
        dfs1(y,x);
        sz[x]+=sz[y];
    }
}

void dfs2(ll x,ll fa){
    root[dfn[x]]=update(root[dfn[x]-1],1,depth,deep[x],sz[x]-1);
    for(auto y:g[x]) if(y!=fa){
        dfs2(y,x);
    }
}

void prepare(){
    depth=0;
    dfs1(1,0);
    root[0]=build(1,depth);
    dfs2(1,0);
}

ll compute(ll a,ll k){
    ll res=(sz[a]-1)*min(k,deep[a]-1);
    res+=query(root[dfn[a]-1],root[dfn[a]+sz[a]-1],1,depth,deep[a]+1,min(depth,deep[a]+k));
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
    prepare();
    for(ll i=1;i<=m;i++){
        ll a,k;
        cin>>a>>k;
        cout<<compute(a,k)<<endl;
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
