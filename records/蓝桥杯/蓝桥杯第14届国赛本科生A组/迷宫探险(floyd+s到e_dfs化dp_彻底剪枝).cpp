//https://www.lanqiao.cn/problems/17103/learning/
//@@@
//dfs,dp,floyd,state compression
//average time:17ms
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
        
    vector<vector<vector<ll>>> f(n,vector<vector<ll>>(1ll<<n,vector<ll>(HP+1,LLONG_MAX/2)));
    f[0][(1ll<<n)-1][HP]=0;
    ll ans=LLONG_MAX/2;
    function<void(ll,ll,ll)> dfs=[&](ll u,ll mask,ll hp)->void{
        if(u==n-1&&mask==0){                   //boundary
            ans=min(ans,f[u][mask][hp]);
            return;
        }
        if(f[u][mask][hp]>=ans) return;        //pruning
        if(u!=n-1&&mask==0){                   //special transition
            if(f[u][mask][hp]+dis[u][n-1]<f[n-1][mask][hp]){
                f[n-1][mask][hp]=f[u][mask][hp]+dis[u][n-1];
                dfs(n-1,mask,hp);
            }
            return;                            //can have no return
        }                                      //The starting point's special transition can be merged into normal transition
        for(ll v=0;v<n;v++){
            ll nmask=mask^1<<v;
            ll nhp=hp-damage_sum[v][mask^1<<v];
            if((mask&1<<v)&&dis[v][u]!=LLONG_MAX/2&&nhp>0){
                if(f[v][nmask][nhp]>f[u][mask][hp]+dis[u][v]){
                    f[v][nmask][nhp]=f[u][mask][hp]+dis[u][v];
                    dfs(v,nmask,nhp);
                }
            }
        }
    };
    dfs(0,(1ll<<n)-1,HP);
    cout<<(ans==LLONG_MAX/2?-1:ans)<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}