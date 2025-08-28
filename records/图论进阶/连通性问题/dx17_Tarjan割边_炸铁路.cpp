//https://www.luogu.com.cn/problem/P1656
//@@@
//tarjan bridge
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=205,M=1e4+5;
ll n,m;
ll h[N],to[M],ne[M],cnte=1;
//    0 1 2 3 4 5
//^1  1 0 3 2 5 4 That's why cnte is initialized as 1

void add_edge(ll u,ll v){
    to[++cnte]=v;
    ne[cnte]=h[u];
    h[u]=cnte;
}

ll dfn[N],low[N],tim,cnt;
vector<array<ll,2>> ans;

void tarjan(ll x,ll ine){
    dfn[x]=low[x]=++tim;
    for(ll i=h[x];i;i=ne[i]){
        ll y=to[i];
        if(!dfn[y]){
            tarjan(y,i);
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]){
                ans.push_back({x,y});
            }
        }else if(i!=(ine^1)){
            low[x]=min(low[x],dfn[y]);
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
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    sort(ans.begin(),ans.end());
    for(auto [x,y]:ans){
        cout<<x<<" "<<y<<endl;
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