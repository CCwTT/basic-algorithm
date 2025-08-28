//https://www.lanqiao.cn/problems/109/learning/?isWithAnswer=true
//typical mistake:reference error caused by the change of the container position 
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<bool>> g(n,vector<bool>(n,false));
    while(m--){
        ll u,v;
        cin>>u>>v;
        u--,v--;
        g[u][v]=g[v][u]=true;
    }
    ll ans=LLONG_MAX;
    vector<vector<ll>> c;
    function<void(ll,ll)> dfs=[&](ll p,ll acc)->void{
        if(acc>=ans) return;
        if(p==n){
            ans=min(ans,acc);
            return;
        }
        for(auto& vec:c){
            bool flag=true;
            for(auto& q:vec){
                if(g[p][q]){
                    flag=false;
                    break;
                }
            }
            if(flag){
                vec.push_back(p);
                dfs(p+1,acc);  //dfs cause the change of the container position
                vec.pop_back();
            }
        }
        c.push_back({p});
        dfs(p+1,acc+1);
        c.pop_back();
    };
    dfs(0,0);
    cout<<ans<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
