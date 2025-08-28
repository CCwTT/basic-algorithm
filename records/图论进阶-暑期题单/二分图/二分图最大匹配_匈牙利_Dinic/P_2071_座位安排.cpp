//https://www.luogu.com.cn/problem/P2071
//@@@
//maximum bipartite matching(Hungarian algorithm)
//O(nm)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=4005;
vector<ll> g[N];
ll vis[N],match[N];

ll n;

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
    cin>>n;
    for(ll u=1;u<=2*n;u++){
        ll v1,v2;
        cin>>v1>>v2;
        g[u].push_back(v1);
        g[u].push_back(v2);
        g[u].push_back(v1+n);
        g[u].push_back(v2+n);
    }
    ll ans=0;
    for(ll i=1;i<=2*n;i++){
        fill(vis,vis+2*n+1,0);
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