//https://www.lanqiao.cn/problems/17103/learning/
//@@@
//dfs,dp,state compression
//TLE
//average time:>1000ms
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
        
    vector<vector<vector<ll>>> f(n,vector<vector<ll>>(1ll<<n,vector<ll>(HP+1,LLONG_MAX/2)));
    f[0][(1ll<<n)-1][HP]=0;
    function<void(ll,ll,ll)> dfs=[&](ll u,ll mask,ll hp)->void{
        if(u==n-1&&mask==0) return;          //boundary
        if(u==0&&mask==(1ll<<n)-1&&hp==HP){  //special transition
            ll nmask=(1ll<<n)-2;
            ll nhp=HP-damage_sum[0][nmask];
            if(nhp>0){
                if(f[0][nmask][nhp]>f[0][mask][hp]){
                    f[0][nmask][nhp]=f[0][mask][hp];
                    dfs(0,nmask,nhp);
                }
            }                                //no return!
        }
        for(auto [w,v]:g[u]){
            if(f[v][mask][hp]>f[u][mask][hp]+w){
                f[v][mask][hp]=f[u][mask][hp]+w;
                dfs(v,mask,hp);
            }
            if(mask&1ll<<v){
                ll nmask=mask^1ll<<v;
                ll nhp=hp-damage_sum[v][nmask];
                if(nhp>0){
                    if(f[v][nmask][nhp]>f[u][mask][hp]+w){
                        f[v][nmask][nhp]=f[u][mask][hp]+w;
                        dfs(v,nmask,nhp);
                    }
                }
            }
        }
    };
    dfs(0,(1ll<<n)-1,HP);
    ll ans=*min_element(f[n-1][0].begin()+1,f[n-1][0].end());
    cout<<(ans==LLONG_MAX/2?-1:ans)<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}