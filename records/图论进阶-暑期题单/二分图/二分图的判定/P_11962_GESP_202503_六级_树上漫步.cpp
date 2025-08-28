//https://www.luogu.com.cn/problem/P11962
//@@@
//coloring method
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;

ll n,m;
vector<ll> g[N];
ll vis[N];
ll b=0,w=0;

void dfs(ll x,ll c){
    vis[x]=c;
    if(c==1) w++;
    else b++;
    for(auto y:g[x]){
        if(!vis[y]){
            dfs(y,3-c);
        }
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,1);
    for(ll i=1;i<=n;i++){
        cout<<(vis[i]==1?w:b)<<" ";
    }
    cout<<endl;
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