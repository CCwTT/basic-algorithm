//https://www.luogu.com.cn/problem/P4592
//@@@
//persistent trie
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf LLONG_MAX/2
typedef long long ll;

const ll MAXN=1e5+5;
const ll lgMAXN=16;
const ll MAXT=MAXN*70;
const ll HIGH=30;
ll n,m;
ll a[MAXN];

vector<ll> g[MAXN];
ll root1[MAXN];
ll root2[MAXN];
struct node{
    ll ch[2];
    ll pass;
};
node tr[MAXT];
ll cnt=0;

ll dep[MAXN];
ll siz[MAXN];
ll stj[MAXN][HIGH+1];
ll dfn[MAXN],cntd=0;

void insert(ll& p,ll pre,ll x){
    p=++cnt;
    tr[p]=tr[pre];
    tr[p].pass++;
    for(ll d=HIGH;d>=0;d--){
        ll path=x>>d&1;
        pre=tr[pre].ch[path];
        cnt++;
        tr[cnt]=tr[pre];
        tr[cnt].pass++;
        tr[cnt-1].ch[path]=cnt;
    }
}

ll query(ll p,ll q,ll x){
    ll res=0;
    for(ll d=HIGH;d>=0;d--){
        ll path=x>>d&1;
        ll best=path^1;
        if(tr[tr[q].ch[best]].pass>tr[tr[p].ch[best]].pass){
            res+=(1<<d);
            p=tr[p].ch[best];
            q=tr[q].ch[best];
        }else{
            p=tr[p].ch[path];
            q=tr[q].ch[path];
        }
    }
    return res;
}

void dfs1(ll x,ll fa){
    insert(root2[x],root2[fa],a[x]);
    dep[x]=dep[fa]+1;
    dfn[x]=++cntd;
    siz[x]=1;
    stj[x][0]=fa;
    for(ll d=1;d<=HIGH;d++){
        stj[x][d]=stj[stj[x][d-1]][d-1];
    }
    for(auto y:g[x]) if(y!=fa){
        dfs1(y,x);
        siz[x]+=siz[y];
    }
}

void dfs2(ll x,ll fa){
    insert(root1[dfn[x]],root1[dfn[x]-1],a[x]);
    for(auto y:g[x]) if(y!=fa){
        dfs2(y,x);
    }
}

ll lca(ll x,ll y){
    if(dep[x]<dep[y]) swap(x,y);
    for(ll d=HIGH;d>=0;d--){
        if(dep[stj[x][d]]>=dep[y]){
            x=stj[x][d];
        }
    }
    if(x==y) return x;
    for(ll d=HIGH;d>=0;d--){
        if(stj[x][d]!=stj[y][d]){
            x=stj[x][d];
            y=stj[y][d];
        }
    }
    return stj[x][0];
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(ll i=1;i<=m;i++){
        ll op,x,y,z;
        cin>>op>>x>>y;
        if(op==1){
            cout<<query(root1[dfn[x]-1],root1[dfn[x]+siz[x]-1],y)<<endl;
        }else{
            cin>>z;
            ll lcafa=stj[lca(x,y)][0];
            cout<<max(query(root2[lcafa],root2[x],z),query(root2[lcafa],root2[y],z))<<endl;
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