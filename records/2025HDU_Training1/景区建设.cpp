//https://acm.hdu.edu.cn/contest/view-code?cid=1172&rid=16688
//@@@
//dfs/bfs,finding trick
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll dx[]={1,-1,0,0};
constexpr ll dy[]={0,0,1,-1};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<ll>> h(n+1,vector<ll>(m+1));
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cin>>h[i][j];
        }
    }
    multiset<array<ll,3>,greater<array<ll,3>>> rest;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            rest.insert({h[i][j],i,j});
        }
    }
    vector<pair<ll,ll>> pts;
    vector<vector<bool>> vis(n+1,vector<bool>(m+1,false));
    function<void(ll,ll)> dfs=[&](ll x,ll y)->void{
        rest.erase(rest.find({h[x][y],x,y}));
        vis[x][y]=true;
        for(ll k=0;k<4;k++){
            ll nx=x+dx[k];
            ll ny=y+dy[k];
            if(nx<1||nx>n||ny<1||ny>m||vis[nx][ny]) continue;
            if(h[nx][ny]<h[x][y]) dfs(nx,ny);
        }
    };
    ll sx=1,sy=1;
    ll ans=0;
    do{
        pts.emplace_back(sx,sy);
        dfs(sx,sy);
        if(!rest.empty()){
            auto [h,x,y]=*rest.begin();
            tie(sx,sy)={x,y};
            ans+=1ll<<34;
        }
    }while(rest.size());
    sort(pts.begin(),pts.end(),[&](const auto& u,const auto& v){
        return h[u.first][u.second]<h[v.first][v.second];
    });
    auto dist=[&](const pair<ll,ll>& a,const pair<ll,ll>& b)->ll{
        auto [x1,y1]=a;
        auto [x2,y2]=b;
        return 114*abs(x1-x2)+5141*abs(y1-y2)+919810*abs(h[x1][y1]-h[x2][y2]);
    };
    for(ll i=1;i<pts.size();i++){
        ans+=dist(pts[i-1],pts[i]);
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