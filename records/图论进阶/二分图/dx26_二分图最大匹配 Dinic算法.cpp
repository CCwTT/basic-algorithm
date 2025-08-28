//https://www.luogu.com.cn/problem/P3386
//@@@
//maximum bipartite matching(Dinic algorithm)
//O(n^0.5m)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1005,M=1e5+5;
struct edge{ll to,c,ne;}e[M<<1];
ll h[N],cnte=1;
ll dep[N],cur[N];

ll n,m,k;
ll src,snk;

void add_edge(ll u,ll v,ll c){
    e[++cnte]={v,c,h[u]};
    h[u]=cnte;
}

bool bfs(){
    memset(dep,0,sizeof(dep));
    queue<ll> q;
    dep[src]=1;
    q.push(src);
    while(!q.empty()){
        ll u=q.front();
        q.pop();
        for(ll i=h[u];i;i=e[i].ne){
            auto [v,c,_]=e[i];
            if(!dep[v]&&c){
                dep[v]=dep[u]+1;
                q.push(v);
                if(v==snk) return true;
            }
        }
    }
    return false;
}

ll dfs(ll u,ll mf){
    if(u==snk) return mf;
    ll res=0;
    for(ll i=cur[u];i;i=e[i].ne){
        cur[u]=i;
        auto [v,c,_]=e[i];
        if(dep[v]==dep[u]+1&&c){
            ll f=dfs(v,min(mf,c));
            e[i].c-=f;
            e[i^1].c+=f;
            res+=f;
            mf-=f;
            if(mf==0) break;
        }
    }
    if(res==0) dep[u]=0;
    return res;
}

ll dinic(){
    ll flow=0;
    while(bfs()){
        memcpy(cur,h,sizeof(h));
        flow+=dfs(src,inf);
    }
    return flow;
}

void solve(){
    cin>>n>>m>>k;
    for(ll i=1;i<=k;i++){
        ll u,v;
        cin>>u>>v;
        add_edge(u,v+n,1);
        add_edge(v+n,u,0);
    }
    src=0,snk=n+m+1;
    for(ll i=1;i<=n;i++){
        add_edge(src,i,1);
        add_edge(i,src,0);
    }
    for(ll i=1;i<=m;i++){
        add_edge(i+n,snk,1);
        add_edge(snk,i+n,0);
    }
    cout<<dinic()<<endl;
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