#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll grid[10][10];
ll dp[10][10][10][10];
ll n;

ll dfs(ll x1,ll y1,ll x2,ll y2){
    if(x1>n||y1>n||x2>n||y2>n) return LLONG_MIN/2;
    if(x1==n&&y1==n&&x2==n&&y2==n) return grid[n][n];
    if(~dp[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
    ll& res=dp[x1][y1][x2][y2];
    res=0;
    res+=grid[x1][y1];
    if(x1!=x2||y1!=y2) res+=grid[x2][y2];
    res+=max({dfs(x1+1,y1,x2+1,y2),dfs(x1+1,y1,x2,y2+1),dfs(x1,y1+1,x2+1,y2),dfs(x1,y1+1,x2,y2+1)});
    return res;
}

void solve(){
    memset(dp,-1,sizeof(dp));
    cin>>n;
    ll x,y,num;
    while(cin>>x>>y>>num&&x&&y&&num){
        grid[x][y]=num;
    }
    cout<<dfs(1,1,1,1)<<endl;
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