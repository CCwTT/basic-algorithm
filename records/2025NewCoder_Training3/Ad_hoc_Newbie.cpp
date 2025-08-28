//https://ac.nowcoder.com/acm/contest/108300/A
//@@@
//constructive algorithm
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=1420;
ll grid[MAXN][MAXN];
ll ans[MAXN][MAXN];
ll n;
pair<ll,ll> f[MAXN];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>f[i].first;
        f[i].second=i;
    }
    sort(f+1,f+n+1);
    queue<ll> free;
    for(ll i=1;i<=n;i++){
        auto [gi,pos]=f[i];
        if(gi==f[i-1].first){
            free.push(i);
            continue;
        }
        for(ll j=i;j<=n;j++){
            grid[i][j]=grid[j][i]=f[i-1].first;
        }
        for(ll t=f[i-1].first+1;t<gi;t++){
            ll j=free.front();
            free.pop();
            for(ll k=j;k<=n;k++){
                grid[j][k]=grid[k][j]=t;
            }
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            ans[f[i].second][f[j].second]=grid[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            grid[i][j]=ans[i][j]=0;
        }
        f[i]={0,0};
    }

}

signed main(){
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}//