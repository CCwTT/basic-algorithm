//https://www.luogu.com.cn/problem/P4782
//@@@
//scc(tarjan),2-SAT
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e6+5;
ll n,m;
ll h[N],to[N],ne[N],cnte; //graph
ll dfn[N],low[N],tim,scc[N],cnt;stack<ll> stk; //tarjan

void add_edge(ll u,ll v){
    to[++cnte]=v;
    ne[cnte]=h[u];
    h[u]=cnte;
}

void tarjan(ll x){
    dfn[x]=low[x]=++tim;
    stk.push(x);
    for(ll i=h[x];i;i=ne[i]){
        ll y=to[i];
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(!scc[y]){
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        ++cnt;
        while(true){
            ll u=stk.top();
            stk.pop();
            scc[u]=cnt;
            if(u==x) break;
        }
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++){
        ll x,v1,y,v2;
        cin>>x>>v1>>y>>v2;
        add_edge(x+!v1*n,y+v2*n);
        add_edge(y+!v2*n,x+v1*n);
    }
    for(ll i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(ll i=1;i<=n;i++){
        if(scc[i]==scc[i+n]){
            cout<<"IMPOSSIBLE"<<endl;
            return;
        }
    }
    cout<<"POSSIBLE"<<endl;
    for(ll i=1;i<=n;i++){
        cout<<(scc[i]>scc[i+n])<<" ";
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