//https://www.luogu.com.cn/record/226238593
//@@@
//rerooting dp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=5e5+5;
ll n,K;
vector<pair<ll,ll>> g[MAXN];
bool a[MAXN];
ll sz[MAXN];
ll sum[MAXN];
ll inner[MAXN],id[MAXN];
ll inner2[MAXN];
ll outer[MAXN];
ll dp[MAXN];

void dfs1(ll x,ll fa){
    sum[x]=0;
    sz[x]=a[x];
    for(auto [w,y]:g[x]) if(y!=fa){
        dfs1(y,x);
        sz[x]+=sz[y];
        if(sz[y]){
            sum[x]+=w+sum[y]+w;
            if(inner[y]+w>inner[x]){
                inner2[x]=inner[x];
                inner[x]=inner[y]+w,id[x]=y;
            }else if(inner[y]+w>inner2[x]){
                inner2[x]=inner[y]+w;
            }
        }
    }
}

void dfs2(ll x,ll fa){
    for(auto [w,y]:g[x]) if(y!=fa){
        if(sz[y]==K){
            dp[y]=dp[x]-2*w;
        }else{
            outer[y]=max(outer[x],y!=id[x]?inner[x]:inner2[x])+w;
            if(sz[y]==0){
                dp[y]=dp[x]+2*w;
            }else{
                dp[y]=dp[x];
            }
        }
        dfs2(y,x);
    }
}

void solve(){
    cin>>n>>K;
    for(ll i=1;i<n;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({w,v});
        g[v].push_back({w,u});
    }
    for(ll i=1;i<=K;i++){
        ll x;
        cin>>x;
        a[x]=true;
    }
    dfs1(1,0);
    dp[1]=sum[1];
    dfs2(1,0);
    for(ll i=1;i<=n;i++){
        cout<<dp[i]-max(inner[i],outer[i])<<endl;
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