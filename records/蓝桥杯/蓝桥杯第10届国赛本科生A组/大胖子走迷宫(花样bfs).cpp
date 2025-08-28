//https://www.lanqiao.cn/problems/234/learning/?isWithAnswer=true
//@@@
//fancy bfs
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll dx[]={0,0,1,-1};
const ll dy[]={1,-1,0,0};

struct Node{
    ll x,y,dis;
    Node(ll x=0,ll y=0,ll dis=0):x(x),y(y),dis(dis){}
};

void solve(){
    ll n,k;
    cin>>n>>k;
    vector<vector<char>> grid(n,vector<char>(n));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    vector<vector<bool>> vis(n,vector<bool>(n,false));
    queue<Node> q;
    vis[2][2]=true;
    q.push({2,2,0});
    while(!q.empty()){
        auto [x,y,dis]=q.front();
        q.pop();
        if(x==n-3&&y==n-3){
            cout<<dis;
            return;
        }
        ll t;
        if(dis<k) t=5;
        else if(dis>=k&&dis<2*k) t=3;
        else if(dis>=2*k) t=1;
        if(t!=1) q.push({x,y,dis+1});
        for(ll i=0;i<4;i++){
            ll nx=x+dx[i];
            ll ny=y+dy[i];
            if(nx-t/2<0||nx+t/2>=n||ny-t/2<0||ny+t/2>=n) continue;
            if(vis[nx][ny]) continue;
            auto check=[&](ll x,ll y)->bool{
                for(ll i=x-t/2;i<=x+t/2;i++)
                    for(ll j=y-t/2;j<=y+t/2;j++)
                        if(grid[i][j]=='*') return false;
                return true;
            };
            if(!check(nx,ny)) continue;
            vis[nx][ny]=true;
            q.push({nx,ny,dis+1});
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}