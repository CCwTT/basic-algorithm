//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1007
//@@@
//SOSDP on tree
/* NEW structure
ll i=0;
for(auto [x,c]:mp){
    ...
    i++;
}
*/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll n,t;
    cin>>n>>t;
    vector<vector<ll>> g(n+1);
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    map<ll,ll> mp;
    ll tt=t;
    for(ll i=2;i*i<=tt;i++){
        while(tt%i==0){
            tt/=i;
            mp[i]++;
        }
    }
    if(tt>1) mp[tt]++;
    const ll w=mp.size();
    auto get=[&](ll x)->ll{
        if(lcm(t,x)!=t){
            return -1;
        }
        ll res=0;
        ll d=0;
        for(auto [p,c]:mp){
            ll cur=0;
            while(x%p==0){
                x/=p;
                cur++;
            }
            if(cur==c){
                res|=1<<d;
            }
            d++;
        }
        return res;
    };
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        ll ai;
        cin>>ai;
        a[i]=get(ai);
    }
    ll ans=0;
    vector<vector<ll>> dp(n+1,vector<ll>(1<<w,0));
    function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
        for(auto y:g[x]) if(y!=fa){
            dfs(y,x);
        }
        if(a[x]==-1) return;
        dp[x][a[x]]++;
        for(auto y:g[x]) if(y!=fa){
            auto s=dp[x];
            for(ll d=0;d<w;d++){
                for(ll mask=0;mask<(1<<w);mask++){
                    if(~mask&(1ll<<d)){
                        s[mask]+=s[mask^(1ll<<d)];
                    }
                }
            }
            for(ll mask=0;mask<(1<<w);mask++){
                ll mask_=mask|a[x];
                ans+=s[((1<<w)-1)^mask_]*dp[y][mask];
                dp[x][mask_]+=dp[y][mask];
            }
        }
        if(a[x]==(1<<w)-1){
            ans++;
        }
    };
    dfs(1,0);
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}