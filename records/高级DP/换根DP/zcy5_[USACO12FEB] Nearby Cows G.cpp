//https://www.luogu.com.cn/problem/P3047
//@@@
//rerooting dp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=1e5+5;
ll n,K;
ll a[MAXN];
vector<ll> g[MAXN];

ll cnt[MAXN][21];
ll cnt2[MAXN][21];
ll dp[MAXN];

void dfs1(ll x,ll fa){
    cnt[x][0]=a[x];
    for(auto y:g[x]) if(y!=fa){
        dfs1(y,x);
        for(ll i=1;i<=K;i++){
            cnt[x][i]+=cnt[y][i-1];
        }
    }
}

void dfs2(ll x,ll fa){
    for(auto y:g[x]) if(y!=fa){
        cnt2[y][0]=dp[y]=a[y];
        for(ll i=1;i<=K;i++){
            cnt2[y][i]=cnt[y][i]+cnt2[x][i-1]-(i==1?0:cnt[y][i-2]);
            dp[y]+=cnt2[y][i];
        }
        dfs2(y,x);
    }
}

void solve(){
    cin>>n>>K;
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(ll i=1;i<=n;i++) cin>>a[i];
    dfs1(1,0);
    for(ll i=0;i<=K;i++){
        dp[1]+=cnt[1][i];
    }
    for(ll i=0;i<=n;i++){
        cnt2[1][i]=cnt[1][i];
    }
    dfs2(1,0);
    for(ll i=1;i<=n;i++){
        cout<<dp[i]<<endl;
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