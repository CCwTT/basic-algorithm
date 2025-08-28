//https://www.luogu.com.cn/problem/P2860
//@@@
//eBCC(tarjan)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5005,M=20005;
ll n,m;
ll h[N],to[M],ne[M],cnte=1;

void add_edge(ll u,ll v){
    to[++cnte]=v;
    ne[cnte]=h[u];
    h[u]=cnte;
}

ll dfn[N],low[N],tim,stk[N],top,dcc[N],cnt;
bool bri[M];
ll deg[N];

void tarjan(ll x,ll ine){
    dfn[x]=low[x]=++tim;
    stk[++top]=x;
    for(ll i=h[x];i;i=ne[i]){
        ll y=to[i];
        if(!dfn[y]){
            tarjan(y,i);
            low[x]=min(low[x],low[y]);
            if(dfn[x]<low[y]){
                bri[i]=bri[i^1]=true;
            }
        }else if(i!=(ine^1)){ 
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        ++cnt;
        while(true){
            ll u=stk[top--];
            dcc[u]=cnt;
            if(u==x) break;
        }
    }
}

void solve(){
    cin>>n>>m;
    while(m--){
        ll u,v;
        cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);
    }
    tarjan(1,0);
    for(ll i=2;i<=cnte;i++){
        if(bri[i]){
            deg[dcc[to[i]]]++;
        }
    }
    ll leaves=0;
    for(ll i=1;i<=cnt;i++){
        if(deg[i]==1){
            leaves++;
        }
    }
    cout<<(leaves+1)/2<<endl;
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