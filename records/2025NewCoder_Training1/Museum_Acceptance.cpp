#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=2e5+5;
ll n;
ll d[MAXN];
ll g[MAXN][4];
ll ans[MAXN][4];
bool vis[MAXN][4];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>d[i];
        for(ll j=1;j<=d[i];j++){
            cin>>g[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        if(!vis[i][1]){
            vector<ll> vec;
            set<pair<ll,ll>> S;
            ll x=i,y=1;
            while(!vis[x][y]){
                if(y==1) vec.push_back(x);
                vis[x][y]=true;
                ll nx=g[x][y];
                S.emplace(min(x,nx),max(x,nx));
                ll ny=find(g[nx]+1,g[nx]+4,x)-g[nx];
                ny=(ny+1-1)%d[nx]+1;
                x=nx,y=ny;
            }
            for(auto x:vec){
                ans[x][1]=S.size();
            }
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<ans[i][1]<<endl;
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