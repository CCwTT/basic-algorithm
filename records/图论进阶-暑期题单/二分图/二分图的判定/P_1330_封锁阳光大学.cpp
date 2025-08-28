//https://www.luogu.com.cn/problem/P1330
//@@@
//coloring method
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

ll n,m;
const ll N=1e5+5;
vector<ll> g[N];
ll vis[N];

ll b,w;

void dfs(ll x,ll c){
    vis[x]=c;
    if(c==1) w++;
    else b++;
    for(auto y:g[x]){
        if(!vis[y]){
            dfs(y,3-c);
        }else if(vis[y]==c){
            cout<<"Impossible";
            exit(0);
        }
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            b=w=0;
            dfs(i,1);
            ans+=min(b,w);
        }
    }
    cout<<ans<<endl;
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