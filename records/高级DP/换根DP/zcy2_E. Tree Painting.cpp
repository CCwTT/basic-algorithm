//https://codeforces.com/problemset/problem/1187/E
//@@@
//rerooting dp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e5+5;
ll n;
vector<ll> g[MAXN];

ll sz[MAXN];
ll dp[MAXN];

void dfs1(ll x,ll fa){
    sz[x]=1;
    for(auto y:g[x]) if(y!=fa){
        dfs1(y,x);
        sz[x]+=sz[y];
    }
    dp[1]+=sz[x];
}

void dfs2(ll x,ll fa){
    for(auto y:g[x]) if(y!=fa){
        dp[y]=dp[x]-sz[y]+(n-sz[y]);
        dfs2(y,x);
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
    dfs1(1,0);
    dfs2(1,0);
    cout<<*max_element(dp+1,dp+n+1)<<endl;
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