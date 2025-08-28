//https://www.lanqiao.cn/problems/17103/learning/
//@@@
//dfs,state compression
//average time:180 ms
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
    vector<vector<pair<ll,ll>>> g(n);
    
    for(ll i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].emplace_back(w,v);
        g[v].emplace_back(w,u);
    }

    vector<vector<ll>> damage_sum(n,vector<ll>(1ll<<n,0));
    for(ll mask=0;mask<(1ll<<n);mask++){
        for(ll u=0;u<n;u++){
            for(auto [w,v]:g[u]){
                if(mask&1ll<<v){
                    damage_sum[u][mask]+=damage[v];
                }
            }
        }
    }
        
   vector<vector<vector<ll>>> mem(n,vector<vector<ll>>(1ll<<n,vector<ll>(HP+1,-1)));
    function<ll(ll,ll,ll)> dfs=[&](ll u,ll mask,ll hp)->ll{
        if(u==0&&mask==(1ll<<n)-1&&hp==HP){    //boundary
            return 0;
        }
        if(~mem[u][mask][hp]) return mem[u][mask][hp];
        ll& res=mem[u][mask][hp];
        res=LLONG_MAX/2; //Why not initialize mem with INF?Because we need to differentiate between not having calculated and being invalid.
        if(u==0&&mask==(1ll<<n)-2&&hp+damage_sum[u][mask]==HP){  //special transition,but it can also be merged into boundary.
            res=min(res,dfs(0,(1ll<<n)-1,HP)+0);
        }
        for(auto [w,v]:g[u]){
            res=min(res,dfs(v,mask,hp)+w);
            if(~mask&1ll<<u){
                ll pmask=mask^1ll<<u;
                ll php=hp+damage_sum[u][mask];
                if(php<=HP){
                    res=min(res,dfs(v,pmask,php)+w);
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