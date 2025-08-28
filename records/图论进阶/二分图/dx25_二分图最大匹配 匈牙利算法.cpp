//https://www.luogu.com.cn/problem/P3386
//@@@
//maximum bipartite matching(Hungarian algorithm)
//O(nm)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=505,M=1e5+5;
vector<ll> g[N];
ll vis[N],match[N];

ll n,m,k;

bool dfs(ll x){
    for(auto y:g[x]){
        if(vis[y]) continue;
        vis[y]=true;
        if(!match[y]||dfs(match[y])){
            match[y]=x;
            return true;
        }
    }
    return false;
}

void solve(){
    cin>>n>>m>>k;
    for(ll i=1;i<=k;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        fill(vis,vis+n+1,0);
        if(dfs(i)){
            ans++;
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