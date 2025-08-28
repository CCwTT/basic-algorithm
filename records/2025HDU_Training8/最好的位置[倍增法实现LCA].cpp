#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=4e5+10;
const ll H=19;
ll n,pos[N];
vector<ll> g[N];

ll dep[N],stj[N][H];

void dfs(ll u,ll fa){
    dep[u]=dep[fa]+1;
    stj[u][0]=fa;
    for(ll d=1;d<H;d++){
        stj[u][d]=stj[stj[u][d-1]][d-1];
    }
    for(auto& v:g[u]) if(v!=fa){
        dfs(v,u);
    }
}

ll lca(ll u,ll v){
    if(dep[u]<dep[v]) swap(u,v);
    for(ll d=H-1;d>=0;d--){
        if(dep[stj[u][d]]>=dep[v]){
            u=stj[u][d];
        }
    }
    if(u==v) return u;
    for(ll d=H-1;d>=0;d--){
        if(stj[u][d]!=stj[v][d]){
            u=stj[u][d];
            v=stj[v][d];
        }
    }
    return stj[u][0];
}

ll dis(ll u,ll v){
    ll x=lca(u,v);
    return dep[u]+dep[v]-2*dep[x];
}

void clear(){
    for(ll i=1;i<=n;i++){
        g[i].clear();
        dep[i]=0;
        for(ll j=0;j<H;j++){
            stj[i][j]=0;
        }
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        ll w;
        cin>>w;
        w++;
        pos[w]=i;
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1,0);
    
    cout<<0<<endl;
    ll s=pos[1];
    ll t=pos[2];

    cout<<(dis(s,t)+1)/2<<endl;
    
    for(ll i=3;i<=n;i++){
        ll x=pos[i];
        if(dis(x,s)<=dis(x,t)){
            if(dis(x,t)>dis(s,t)){
                s=x;
            }
        }else{
            if(dis(s,x)>dis(s,t)){
                t=x;
            }
        }
        cout<<(dis(s,t)+1)/2<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}