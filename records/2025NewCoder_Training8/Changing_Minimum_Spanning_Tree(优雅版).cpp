//https://ac.nowcoder.com/acm/contest/108305/G
//@@@
//graph theory,heuristic merging
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1e5+5,MOD=1e9+7;
ll n,m,k;
vector<vector<ll>> g,f;
vector<al3> edges;
ll dsu[N],siz[N];

ll find(ll x){
    return dsu[x]==x?x:dsu[x]=find(dsu[x]);
}

void solve(){
    cin>>n>>m>>k;
    edges.clear();
    g.assign(n+1,vector<ll>());
    f.assign(n+1,vector<ll>());
    iota(dsu,dsu+n+1,0);
    fill(siz,siz+n+1,1);
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,u,v});
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sort(edges.begin(),edges.end());
    ll cw=1;
    ll ans=0;
    ll sub=0;
    ll tot=n*(n-1)/2-m;

    function<void(ll,ll)> dfs=[&](ll u,ll fv){
        for(ll v:f[u]){
            dfs(v,fv);
        }
        for(ll v:g[u]){
            if(find(v)==fv) sub--;
        }
    };
    for(ll i=0;i<m;i++){
        auto [w,u,v]=edges[i];
        if(cw!=w){
            (ans+=(tot-sub)%MOD*(w-cw))%=MOD;
            cw=w;
        }
        ll fu=find(u);
        ll fv=find(v);
        if(fu==fv) continue;
        if(siz[fv]>siz[fu]){
            swap(fu,fv);
        }
        sub+=siz[fu]*siz[fv];
        dfs(fv,fu);
        sub%=MOD;
        siz[fu]+=siz[fv];
        dsu[fv]=fu;
        f[fu].push_back(fv);
    }
    set<ll> st;
    for(ll i=1;i<=n;i++){
        st.insert(find(i));
    }
    if(st.size()==2){
        cout<<siz[*st.begin()]*siz[*st.rbegin()]%MOD*k%MOD<<endl;
        return;
    }
    if(st.size()>2){
        cout<<0<<endl;
        return;
    }
    cout<<(ans+MOD)%MOD<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}