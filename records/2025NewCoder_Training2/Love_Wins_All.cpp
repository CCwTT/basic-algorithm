//https://ac.nowcoder.com/acm/contest/108299/L
//@@@
//classification,addtion&multiplication principle
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

const ll mod=998244353;
const ll MAXN=5e5+5;
ll n;
ll g[MAXN];
bool vis[MAXN];

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

ll dfs(ll x){
    if(vis[x]) return 0;
    vis[x]=1;
    return 1+dfs(g[x]);
}

void solve(){
    cin>>n;
    memset(vis,0,sizeof(bool)*(n+1));
    for(ll i=1;i<=n;i++){
        cin>>g[i];
    }
    vector<ll> odd;
    vector<ll> even1;
    vector<ll> even2;
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            ll ret=dfs(i);
            if(ret&1) odd.push_back(ret);
            else{
                if(ret==2) even1.push_back(ret);
                else even2.push_back(ret);
            }
        }
    }
    if(odd.size()!=0&&odd.size()!=2){
        cout<<0<<endl;
        return;
    }
    if(odd.size()==2){
        cout<<odd[0]*odd[1]%mod*qpow(2,even2.size())%mod<<endl;
        return;
    }
    ll ans=0;
    for(auto x:even1){
        ans=(ans+(x/2)%mod*(x/2)%mod*qpow(2,even2.size()))%mod;
    }
    for(auto x:even2){
        ans=(ans+(x/2)%mod*(x/2)%mod*qpow(2,even2.size()-1))%mod;
    }
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T; 
    while(T--){
        solve();
    }
    return 0;
}