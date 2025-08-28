//https://www.luogu.com.cn/problem/P8435
//@@@
//vBCC(tarjan)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5e5+5;
ll n,m;
vector<ll> g[N],bcc[N];
ll dfn[N],low[N],tim; stack<ll> stk;
bool apt[N];ll cnt;

void tarjan(ll x,ll src){
    // if(x==src&&g[x].size()==0){
    //     bcc[++cnt].push_back(x);
    //     return;
    // }
    dfn[x]=low[x]=++tim;
    stk.push(x);
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y,src);
            low[x]=min(low[x],low[y]);
            if(low[y]==dfn[x]){ //>=
                if(g[x].size()>1){  //之前有个son,现在改成deg
                    apt[x]=true;
                }
                cnt++;
                while(true){
                    ll u=stk.top();
                    stk.pop();
                    bcc[cnt].push_back(u);
                    if(u==y) break;
                }
                bcc[cnt].push_back(x);
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
        if(u==v) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            if(g[i].size()==0){      //new
                bcc[++cnt].push_back(i);
            }else{
                tarjan(i,i);
            }
        }
    }
    cout<<cnt<<endl;
    for(ll i=1;i<=cnt;i++){
        cout<<bcc[i].size()<<" ";
        for(auto x:bcc[i]){
            cout<<x<<" ";
        }
        cout<<endl;
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