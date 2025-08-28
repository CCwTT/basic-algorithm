//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1010
//@@@
//Tarjan's SCC condensation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=5e5+10;
ll n,dfn[N],low[N],ins[N],tim,cnt;
ll a[N],b[N];
ll scc[N],siz[N];
bool mark[N];
stack<ll> stk;
vector<vl> g(N);
vector<vl> G(N);
bool vis1[N];
bool vis2[N];
ll ans;

void dfs1(ll u){
    vis1[u]=true;
    for(auto v:g[u]){
        if(!vis1[v]){
            dfs1(v);
        }
    }
}

void dfs2(ll u){
    vis2[u]=true;
    ans+=siz[u];
    for(auto v:G[u]){
        if(!vis2[v]){
            dfs2(v);
        }
    }
}

void tarjan(ll x){
    dfn[x]=low[x]=++tim;
    stk.push(x);
    ins[x]=1;
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(ins[y]){
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        cnt++;
        while(true){
            ll u=stk.top();
            stk.pop();
            ins[u]=0;
            scc[u]=cnt;
            mark[cnt]|=vis1[u];
            siz[cnt]++;
            if(u==x) break;
        }
    }
}

void clear(){
    tim=0;
    cnt=0;
    stack<ll>().swap(stk);
    ans=0;
    for(ll i=0;i<=n;i++){
        dfn[i]=low[i]=ins[i]=scc[i]=siz[i]=mark[i]=vis1[i]=vis2[i]=0;
        g[i].clear();
        G[i].clear();
    }
}


void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    for(ll i=1;i<=n;i++) cin>>b[i];
    for(ll i=1;i<=n;i++)
        for(ll j=1,v;j<=b[i];j++){
            cin>>v;
            g[i].push_back(v);
        }
    for(ll i=1;i<=n;i++)
        if(a[i]) dfs1(i);
    for(ll i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(ll i=1;i<=n;i++){
        for(auto j:g[i]){
            if(scc[i]!=scc[j]){
                G[scc[i]].push_back(scc[j]);
            }
        }
    }
    for(ll i=1;i<=cnt;i++){
        if(!vis2[i]&&mark[i]&&siz[i]>1){
            dfs2(i);
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}