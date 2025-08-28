//https://www.lanqiao.cn/problems/17103/learning/
//@@@
//dfs,floyd,state compression
//average time:70ms
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n,m,HP;
    cin>>n>>m>>HP;
    vector<ll> damage(n);
    for(ll i=0;i<n;i++){
        cin>>damage[i];
    } 
    vector<vector<ll>> dis(n,vector<ll>(n,LLONG_MAX/2));
    for(ll i=0;i<n;i++){
        dis[i][i]=0;
    }
    vector<vector<bool>> adj(n,vector<bool>(n,false));
    for(ll i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=dis[v][u]=w;
        adj[u][v]=adj[v][u]=true;
    }
    for(ll k=0;k<n;k++){
        for(ll i=0;i<n;i++){
            for(ll j=0;j<n;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }

    vector<vector<ll>> damage_sum(n,vector<ll>(1ll<<n,0));
    for(ll mask=0;mask<(1ll<<n);mask++){
        for(ll i=0;i<n;i++){
            for(ll j=0;j<n;j++){
                if(adj[i][j]&&(mask&1<<j)){
                    damage_sum[i][mask]+=damage[j];
                }
            }
        }
    }
        
    vector<vector<vector<ll>>> mem(n,vector<vector<ll>>(1ll<<n,vector<ll>(HP+1,-1)));
    function<ll(ll,ll,ll)> dfs=[&](ll u,ll mask,ll hp)->ll{
        if(__builtin_popcountll(~mask&((1ll<<n)-1))==1&&hp+damage_sum[u][mask]==HP){    //boundary
            return dis[0][u];
        }
        if(~mem[u][mask][hp]) return mem[u][mask][hp];
        ll& res=mem[u][mask][hp];
        res=LLONG_MAX/2; //Why not initialize mem with INF?Because we need to differentiate between not having calculated and being invalid.
        if(u==n-1&&mask==0){                  //special transition
            for(ll v=0;v<n-1;v++){
                res=min(res,dfs(v,0,hp)+dis[v][u]);
            }
        }
        for(ll v=0;v<n;v++){
            if(v!=u&&(~mask&1ll<<v)){
                ll pmask=mask^1ll<<u;
                ll php=hp+damage_sum[u][mask];
                if(php<=HP){
                    res=min(res,dfs(v,pmask,php)+dis[v][u]);
                }
            }
        }
        return res;
    };
    ll ans=LLONG_MAX/2;
    for(ll hp=1;hp<=HP;hp++){
        ans=min(ans,dfs(n-1,0,hp));
    }
    cout<<(ans==LLONG_MAX/2?-1:ans)<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}