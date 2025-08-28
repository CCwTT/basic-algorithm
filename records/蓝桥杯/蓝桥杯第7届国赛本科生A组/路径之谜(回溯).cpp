//https://www.lanqiao.cn/problems/89/learning/?isWithAnswer=true
//@@@
//backtrace
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll dx[4]={1,-1,0,0};//控制走的方向
const ll dy[4]={0,0,1,-1};

void solve(){
    ll n;
    cin>>n;
    vector<ll> cntx(n+1),cnty(n+1);
    for(ll i=1;i<=n;i++){
        cin>>cnty[i];
    }
    for(ll i=1;i<=n;i++){
        cin>>cntx[i];
    }

    vector<vector<bool>> vis(n+1,vector<bool>(n+1,false));
    vector<ll> path;
    function<void(ll,ll)> dfs=[&](ll x,ll y)->void{
        vis[x][y]=true;
        path.push_back((x-1)*n+y-1);
        cntx[x]--,cnty[y]--;
        auto check=[&]()->bool{
            for(ll i=1;i<=n;i++){
                if(cntx[i]||cnty[i]) return false;
            }
            return true;
        };
        if(x==n&&y==n&&check()){
            for(auto x:path){
                cout<<x<<" ";
            }
            cout<<endl;
            return;
        }
        for(ll k=0;k<4;k++){
            ll nx=x+dx[k];
            ll ny=y+dy[k];
            if(nx<1||nx>n||ny<1||ny>n) continue;
            if(vis[nx][ny]) continue;
            if(cntx[nx]&&cnty[ny]){
                dfs(nx,ny);
                cntx[nx]++,cnty[ny]++;
                path.pop_back();
                vis[nx][ny]=false;
            }
        }
    };
    dfs(1,1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
