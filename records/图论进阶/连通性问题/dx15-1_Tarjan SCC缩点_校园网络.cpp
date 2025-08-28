//https://www.luogu.com.cn/problem/P2812
//@@@
//tarjan-scc
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
ll n,m;
vector<ll> g[N];

ll dfn[N],low[N],tim=0;
stack<ll> stk;
bool ins[N];
ll scc[N],siz[N],cnt=0;

ll ind[N],oud[N];

void tarjan(ll x){
    dfn[x]=low[x]=++tim;
    ins[x]=true;
    stk.push(x);
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(ins[y]){
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        cnt++;
        while(true){
            ll u=stk.top();
            stk.pop();
            ins[u]=false;
            scc[u]=cnt;
            siz[cnt]++;
            if(u==x) break;
        }
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        ll j;
        while(cin>>j&&j){
            g[i].push_back(j);
        }
    }
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(ll i=1;i<=n;i++){
        for(auto j:g[i]){
            if(scc[i]!=scc[j]){
                ind[scc[j]]++;
                oud[scc[i]]++;
            }
        }
    }
    ll ans1=0,ans2=0;
    for(ll i=1;i<=cnt;i++){
        if(ind[i]==0) ans1++;
        if(oud[i]==0) ans2++;
    }
    cout<<ans1<<endl<<(cnt==1?0:max(ans1,ans2))<<endl;
}
    
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}