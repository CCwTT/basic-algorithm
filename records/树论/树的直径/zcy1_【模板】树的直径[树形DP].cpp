//https://www.luogu.com.cn/problem/P3304
//@@@
//tree diameter(tree dp)
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
ll ans=0;

ll dfs(ll u,ll fa){
    ll dl=0,sl=0;
    for(auto& [w,v]:g[u]) if(v!=fa){
        ll dl_=dfs(v,u)+w;
        chmax(sl,dl_+dl);
        chmax(dl,dl_);
        chmax(ans,sl);
    }
    return dl;
}

void solve(){
    cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].emplace_back(w,v);
        g[v].emplace_back(w,u);
    }
    dfs(1,0);
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