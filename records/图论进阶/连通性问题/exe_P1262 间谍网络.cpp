//https://www.luogu.com.cn/problem/P1262
//@@@
//tarjan scc condensation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=3005;
ll n,m,K;
ll a[N];
vector<ll> g[N],G[N];

ll dfn[N],low[N],tim;
stack<ll> stk;
bool ins[N];

ll scc[N],b[N],mi[N],cnt;
ll ind[N];
bool vis[N];

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
        while(true){
            ll u=stk.top();
            stk.pop();
            ins[u]=false;
            scc[u]=cnt;
            b[cnt]=min(b[cnt],a[u]);
            mi[cnt]=min(mi[cnt],u);
            if(u==x) break;
        }
    }
}

void solve(){
    cin>>n>>K;
    fill(a+1,a+n+1,inf);
    fill(b+1,b+n+1,inf);
    fill(mi+1,mi+n+1,inf);
    for(ll i=1;i<=K;i++){
        ll x;
        cin>>x;
        cin>>a[x];
    }
    cin>>m;
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
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
            }
        }
    }
    ll ans=0;
    for(ll i=1;i<=cnt;i++){
        if(ind[i]==0){
            if(b[i]==inf){
                cout<<"NO"<<endl;
                for(ll j=1;j<=n;j++){
                    for(auto k:g[j]){
                        if(scc[j]!=scc[k]){
                            G[scc[j]].push_back(scc[k]);
                        }
                    }
                }
                queue<ll> q;
                for(ll j=1;j<=cnt;j++){
                    if(b[j]!=inf){
                        vis[j]=true;
                        q.push(j);
                    }
                }
                while(!q.empty()){
                    ll u=q.front();
                    q.pop();
                    for(auto v:G[u]){
                        if(!vis[v]){
                            vis[v]=true;
                            q.push(v);
                        }
                    }
                }
                ll mn=inf;
                for(ll j=1;j<=cnt;j++){
                    if(!vis[j]){
                        mn=min(mn,mi[j]);
                    }
                }
                cout<<mn<<endl;
                return;
            }
            ans+=b[i];
        }
    }
    cout<<"YES"<<endl;
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