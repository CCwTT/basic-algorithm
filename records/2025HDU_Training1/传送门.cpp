//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1005
//@@@
//extra information maintenance,map,dijkstra
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<pair<ll,ll>>> g(n+1);
    for(ll i=1;i<=m;i++){
        ll u,v,c;
        cin>>u>>v>>c;
        g[u].emplace_back(c,v);
        g[v].emplace_back(c,u);
    }
    map<pair<ll,ll>,ll> dis;
    dis[{1,0}]=0;
    priority_queue<array<ll,3>,vector<array<ll,3>>,greater<array<ll,3>>> pq;
    pq.push({0,1,0});
    while(!pq.empty()){
        auto [disx,x,from]=pq.top();
        pq.pop();
        if(disx>dis[{x,from}]) continue;
        for(auto [c,y]:g[x]){
            ll disy=disx+(c!=from);
            if(!dis.count({y,c})||disy<dis[{y,c}]){
                dis[{y,c}]=disy;
                pq.push({disy,y,c});
            }
        }
    }
    ll ans=inf;
    for(auto [c,y]:g[n]){
        ans=min(ans,dis[{n,c}]);
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}