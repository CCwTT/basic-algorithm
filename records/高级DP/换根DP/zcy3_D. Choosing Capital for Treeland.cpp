//https://codeforces.com/problemset/problem/219/D
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
map<pair<ll,ll>,ll> from;

ll dp[MAXN];

void dfs1(ll x,ll fa){
    for(auto y:g[x]) if(y!=fa){
        dfs1(y,x);
        dp[1]+=from[{x,y}]==y;
    }
}

void dfs2(ll x,ll fa){
    for(auto y:g[x]) if(y!=fa){
        dp[y]=dp[x]+(from[{x,y}]==x)-(from[{x,y}]==y);
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
        from[{u,v}]=from[{v,u}]=u;
    }
    dfs1(1,0);
    dfs2(1,0);
    ll mn=2e6;
    vector<ll> ans;
    for(ll i=1;i<=n;i++){
        if(dp[i]<mn){
            mn=dp[i];
            ans.clear();
            ans.push_back(i);
        }else if(dp[i]==mn){
            ans.push_back(i);
        }
    }
    cout<<mn<<endl;
    for(auto x:ans) cout<<x<<" ";
    cout<<endl;
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