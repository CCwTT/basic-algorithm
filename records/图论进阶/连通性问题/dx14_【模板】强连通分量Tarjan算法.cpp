//https://www.luogu.com.cn/problem/P2863
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
ll dfn[N],low[N];
stack<ll> stk;
bool ins[N];
ll scc[N],siz[N];
ll tim=0,cnt=0;

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
        ++cnt;
        ll u;
        do{
            u=stk.top();
            stk.pop();
            ins[u]=0;
            scc[u]=cnt;
            siz[cnt]++;
        }while(u!=x);
    }
}

void solve(){
    cin>>n>>m;
    while(m--){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    ll ans=0;
    for(ll i=1;i<=cnt;i++){
        if(siz[i]>1){
            ans++;
        }
    }
    cout<<ans<<endl;
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