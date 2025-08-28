//https://www.lanqiao.cn/problems/1022/learning/
//@@@
//backtrack model
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll dx[]={0,0,1,-1};
const ll dy[]={1,-1,0,0};

void solve(){
    ll n=4;
    vector<vector<ll>> grid(n,vector<ll>(n,-1));
    
    ll ans=0;
    function<void(ll,ll,ll)> dfs=[&](ll p,ll x,ll y){
        if(p==n*n){
            ans++;
            return;
        }
        for(ll k=0;k<4;k++){
            ll nx=x+dx[k];
            ll ny=y+dy[k];
            if(nx<0||ny<0||nx>=n||ny>=n) continue;
            if(~grid[nx][ny]) continue;
            grid[nx][ny]=p+1;
            dfs(p+1,nx,ny);
            grid[nx][ny]=-1;
        }
    };
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            grid[i][j]=1;
            dfs(1,i,j);
            grid[i][j]=-1;
        }
    }
    cout<<ans<<endl;
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
