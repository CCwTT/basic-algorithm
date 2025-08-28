//https://www.luogu.com.cn/problem/P3388
//@@@
//articulation point
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,m;
vector<ll> g[N];
ll dfn[N],low[N],tim;
bool apt[N];

void tarjan(ll x,ll root){
    dfn[x]=low[x]=++tim;
    ll cntc=0;
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y,root);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                cntc++;
                if(x!=root||cntc>1){
                    apt[x]=true;
                }
            }
        }else{
            low[x]=min(low[x],dfn[y]);
        }
    }
}

void solve(){
    cin>>n>>m;
    while(m--){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans+=apt[i];
    }
    cout<<ans<<endl;
    for(ll i=1;i<=n;i++){
        if(apt[i]){
            cout<<i<<" ";
        }
    }
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