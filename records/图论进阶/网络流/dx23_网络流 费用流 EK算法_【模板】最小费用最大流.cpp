//https://www.luogu.com.cn/problem/P3381
//@@@
//MCFM(EK)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5005,M=1e5+5;
struct edge{ll to,c,w,ne;}e[M];
ll h[N],cnte=1;
ll dis[N],mf[N],pre[N];
bool inq[N];

ll n,m,src,snk;

void add_edge(ll u,ll v,ll c,ll w){
    e[++cnte]={v,c,w,h[u]};
    h[u]=cnte;
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(mf,0,sizeof(mf));
    queue<ll> q;
    dis[src]=0;
    mf[src]=inf;
    inq[src]=true;
    q.push(src);
    while(!q.empty()){
        ll u=q.front();
        q.pop();
        inq[u]=false;
        for(ll i=h[u];i;i=e[i].ne){
            auto [v,c,w,_]=e[i];
            if(dis[v]>dis[u]+w&&c){
                dis[v]=dis[u]+w;
                pre[v]=i;
                mf[v]=min(mf[u],c);
                if(!inq[v]){
                    inq[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return mf[snk]>0;
}

pair<ll,ll> EK(){
    ll flow=0,cost=0;
    while(spfa()){
        for(ll u=snk;u!=src;){
            ll i=pre[u];
            e[i].c-=mf[snk];
            e[i^1].c+=mf[snk];
            u=e[i^1].to;
        }
        flow+=mf[snk];
        cost+=mf[snk]*dis[snk];
    }
    return {flow,cost};
}

void solve(){
    cin>>n>>m>>src>>snk;
    for(ll i=1;i<=m;i++){
        ll u,v,c,w;
        cin>>u>>v>>c>>w;
        add_edge(u,v,c,w);
        add_edge(v,u,0,-w);
    }
    auto [flow,cost]=EK();
    cout<<flow<<" "<<cost<<endl;
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