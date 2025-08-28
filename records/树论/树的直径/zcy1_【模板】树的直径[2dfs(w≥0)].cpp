//https://www.luogu.com.cn/problem/P3304
//Not all test cases are passed owing to the existence of negative edges
//tree diameter(2 dfs)
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

const ll N=5e5+5;
ll n;
vector<pll> g[N];
ll ans,s,t;
ll dis[N],pa[N];

void dfs(ll u,ll fa,ll fw){
    dis[u]=dis[fa]+fw;
    pa[u]=fa;
    for(auto& [w,v]:g[u]) if(v!=fa){
        dfs(v,u,w);
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].emplace_back(w,v);
        g[v].emplace_back(w,u);
    }
    dfs(1,0,0);
    ll mx=-1;
    for(ll i=1;i<=n;i++){
        if(chmax(mx,dis[i])){
            s=i;
        }
    }
    dfs(s,0,0);
    ans=-1;
    for(ll i=1;i<=n;i++){
        if(chmax(ans,dis[i])){
            t=i;
        }
    }
    cout<<ans<<endl;
}

void clear(){

}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}