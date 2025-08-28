//https://ac.nowcoder.com/acm/contest/108302/J
//@@@
//binary search,bfs,grid oe
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

using namespace std;
using pii=pair<ll,ll>;

constexpr ll N=2e5+10;
ll n,m;
ll dx[]={1,0,-1,0};
ll dy[]={0,1,0,-1};


void solve(){
    cin>>n>>m;
    vector<vector<ll>> g(n,vector<ll>(m));
    vector<vector<ll>> t(n,vector<ll>(m,inf));
    vector<vector<bool>> vis(n,vector<bool>(m));
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            cin>>g[i][j];
    queue<pii> q;
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            if(g[i][j]){
                vis[i][j]=true;
                t[i][j]=0;
                q.emplace(i,j);
            }
    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        for(ll i=0;i<4;i++){
            ll nx=x+dx[i],ny=y+dy[i];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(vis[nx][ny]) continue;
            t[nx][ny]=t[x][y]+1;
            q.emplace(nx,ny);
            vis[nx][ny]=true;
        }
    }
    auto check=[&](ll x)->bool{
        ll mx1=inf,mx2=inf;
        ll mi1=-inf,mi2=-inf;
        for(ll i=0;i<n;i++)
            for(ll j=0;j<m;j++)
                if(t[i][j]>x){
                    mx1=min(mx1,j+i+x);
                    mi1=max(mi1,j+i-x);
                    mx2=min(mx2,j-i+x);
                    mi2=max(mi2,j-i-x);
                }
        if(mx1==mi1&&mx2==mi2){
            if((mx1+mx2)&1) return false;
            else return true;
        }
        return mx1>=mi1&&mx2>=mi2;
    };
    ll l=0,r=n*m;
    while(l<r){
        ll mid=l+r>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}