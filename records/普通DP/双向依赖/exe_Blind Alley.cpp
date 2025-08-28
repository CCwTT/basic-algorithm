//https://ac.nowcoder.com/acm/contest/108301/B
//@@@
//grid graph,dp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr int N=-1;
constexpr int dx0[]={-1,1,0};
constexpr int dy0[]={0,0,-1};
constexpr int dx1[]={-1,1,0};
constexpr int dy1[]={0,0,1};

void solve(){
    int n,m,K;
    cin>>n>>m>>K;
    vector<vector<int>> grid0(n+2,vector<int>(m+2));
    vector<vector<int>> grid(n+2,vector<int>(m+2));
    vector<vector<bool>> vis0(n+1,vector<bool>(m+1,false));
    vector<vector<bool>> vis1(n+1,vector<bool>(m+1,false));
    
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=1;j<=m;j++){
            grid0[i][j]=s[j-1]-'0';
        }
    }
    
    function<void(int,int)> dfs0=[&](int x,int y){
        vis0[x][y]=true;
        for(int k=0;k<3;k++){
            int nx=x+dx0[k];
            int ny=y+dy0[k];
            if(nx<1||ny<1||nx>n||ny>m) continue;
            if(vis0[nx][ny]||grid0[nx][ny]==1) continue;
            dfs0(nx,ny);
        }
    };
    dfs0(1,m);
    
    function<void(int,int)> dfs1=[&](int x,int y){
        vis1[x][y]=true;
        for(int k=0;k<3;k++){
            int nx=x+dx1[k];
            int ny=y+dy1[k];
            if(nx<1||ny<1||nx>n||ny>m) continue;
            if(vis1[nx][ny]||grid0[nx][ny]==1) continue;
            dfs1(nx,ny);
        }
    };
    dfs1(1,1);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(vis1[i][j]&&!vis0[i][j]){
                grid[i][j]=1;
            }
        }
    }
    
    vector<vector<ll>> dp(n+2,vector<ll>(m+2,0));
    for(ll j=m;j>=1;j--){
        for(ll i=n;i>=1;i--){
            if(grid[i][j]==1){
                dp[i][j]=1;
                if(grid[i][j+1]==1){
                    dp[i][j]=max(dp[i][j],dp[i][j+1]+1);
                }
                if(grid[i+1][j]==1){
                    dp[i][j]=max(dp[i][j],dp[i+1][j]);
                }
            }
        }
        for(ll i=1;i<=n;i++){
            if(grid[i][j]==1){
                if(grid[i-1][j]==1){
                    dp[i][j]=max(dp[i][j],dp[i-1][j]);
                }
                if(dp[i][j]>=K){
                    cout<<"Yes"<<endl;
                    return;
                }
            }
        }
    }
    cout<<"No"<<endl;
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