//https://www.luogu.com.cn/problem/P2756
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

ll n,m;

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
    cin>>m>>n;
    ll u,v;
    while(cin>>u>>v&&~u&&~v){
        v-=m;
        g[u].push_back(v);
    }
    ll tot=0;
    for(ll i=1;i<=n;i++){
        fill(vis,vis+n+1,0);
        if(dfs(i)){
            tot++;
        }
    }
    cout<<tot<<endl;
    for(ll i=1;i<=n-m;i++){
        if(match[i]){
            cout<<match[i]<<" "<<i+m<<endl;
        }
    }
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