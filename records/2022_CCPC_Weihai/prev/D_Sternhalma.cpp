#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[19];
ll dp[(1ll<<20)+5];
vector<pair<ll,ll>> g[19];

void init0(){
    fill(dp,dp+((1ll<<20)+5),LLONG_MIN);
}

ll dfs(ll mask){
    if(mask==0) return 0;
    if(dp[mask]!=LLONG_MIN) return dp[mask];
    ll& res=dp[mask];
    for(ll i=0;i<19;i++){
        if(mask&(1ll<<i)){
            ll nmask=mask^(1ll<<i);
            res=max(res,dfs(nmask));
            for(auto [mid,to]:g[i]){
                if((mask&(1ll<<mid))&&(~mask&(1ll<<to))){
                    ll nmask=mask^(1ll<<to)^(1ll<<i)^(1ll<<mid);
                    res=max(res,a[mid]+dfs(nmask));
                }
            }
        }
    }
    return res;
}

void solve(){
    ll mask=0;
    for(ll i=0;i<19;i++){
        char c;
        cin>>c;
        if(c=='#'){
            mask|=(1ll<<i);
        }
    }
    cout<<dfs(mask)<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init0();
    g[0]={{1,2},{4,9},{3,7}};
    g[1]={{4,8},{5,10}};
    g[2]={{1,0},{5,9},{6,11}};
    g[3]={{4,5},{8,13}};
    g[4]={{5,6},{9,14},{8,12}};
    g[5]={{10,15},{9,13},{4,3}};
    g[6]={{10,14},{5,4}};
    g[7]={{3,0},{8,9},{12,16}};
    g[8]={{4,1},{9,10},{13,17}};
    g[9]={{5,2},{10,11},{14,18},{13,16},{8,7},{4,0}};
    g[10]={{14,17},{9,8},{5,1}};
    g[11]={{15,18},{10,9},{6,2}};
    g[12]={{8,4},{13,14}};
    g[13]={{9,5},{14,15},{8,3}};
    g[14]={{10,6},{13,12},{9,4}};
    g[15]={{14,13},{10,5}};
    g[16]={{13,9},{17,18},{12,7}};
    g[17]={{14,10},{13,8}};
    g[18]={{15,11},{17,16},{14,9}};
    for(ll i=0;i<19;i++){
        cin>>a[i];
    }
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}