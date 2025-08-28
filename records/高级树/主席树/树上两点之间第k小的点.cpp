//https://www.luogu.com.cn/problem/P2633
//@@@
//persistent discretized segment tree,lca
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

const ll MAXN=1e5+5;
const ll MAXT=MAXN*50;
const ll MAXH=20;

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
        disc.erase(unique(disc.begin()+1,disc.end()),disc.end());
        return disc.size()-1;
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
};
discretizer disc;

ll n,m,b;
ll a[MAXN];
int root[MAXN];
int lc[MAXT];
int rc[MAXT];
ll sum[MAXT];
ll cnt=0;

vector<ll> g[MAXN];
ll deep[MAXN];
ll stj[MAXN][MAXH];

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

ll update(ll p,ll l,ll r,ll x){
    p=clone(p);
    if(l==r){
        sum[p]++;
    }else{
        ll m=l+r>>1;
        if(x<=m) lc[p]=update(lc[p],l,m,x);
        if(x>m) rc[p]=update(rc[p],m+1,r,x);
        up(p);
    }
    return p;
}

ll query(ll u,ll v,ll lca,ll lcafa,ll l,ll r,ll k){
    if(l==r){
        return l;
    }
    ll lsum=sum[lc[u]]+sum[lc[v]]-sum[lc[lca]]-sum[lc[lcafa]];
    ll m=l+r>>1;
    if(k<=lsum) return query(lc[u],lc[v],lc[lca],lc[lcafa],l,m,k);
    else return query(rc[u],rc[v],rc[lca],rc[lcafa],m+1,r,k-lsum);
}

void dfs(ll x,ll fa){
    root[x]=update(root[fa],1,b,disc.query(a[x]));
    deep[x]=deep[fa]+1;
    stj[x][0]=fa;
    for(ll d=1;d<MAXH;d++){
        stj[x][d]=stj[stj[x][d-1]][d-1];
    }
    for(auto y:g[x]) if(y!=fa){
        dfs(y,x);
    }
}

ll lca(ll x,ll y){
    if(deep[x]<deep[y]) swap(x,y);
    for(ll d=MAXH-1;d>=0;d--){
        if(deep[stj[x][d]]>=deep[y]){
            x=stj[x][d];
        }
    }
    if(x==y) return x;
    for(ll d=MAXH-1;d>=0;d--){
        if(stj[x][d]!=stj[y][d]){
            x=stj[x][d];
            y=stj[y][d];
        }
    }
    return stj[x][0];
}

ll kth(ll u,ll v,ll k){
    ll lca_node=lca(u,v);
    return disc.disc[query(root[u],root[v],root[lca_node],root[stj[lca_node][0]],1,b,k)];
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        disc.insert(a[i]);
    }
    b=disc.discretize();
    root[0]=build(1,b);
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    ll last_ans=0;
    for(ll i=1;i<=m;i++){
        ll u,v,k;
        cin>>u>>v>>k;
        u^=last_ans;
        last_ans=kth(u,v,k);
        cout<<last_ans<<endl;
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
