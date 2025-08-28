//https://www.luogu.com.cn/problem/P3381
//@@@
//MCMF
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=5010;
const ll M=100010;

struct edge{
    ll to,c,w,ne; 
}e[M*2]; 
ll h[N],cnte=1; 
ll dis[N];
ll cur[N]; 
bool vis[N]; 

ll n,m,src,snk; 
ll flow,cost; 


void add_edge(ll u,ll v,ll c,ll w){
    e[++cnte]={v,c,w,h[u]};
    h[u]=cnte;
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    memcpy(cur,h,sizeof(h));
    deque<ll> q; 
    dis[src]=0;
    vis[src]=true;
    q.push_back(src);
    while(!q.empty()){
        ll u=q.front();
        q.pop_front();
        vis[u]=false;
        for(ll i=h[u];i;i=e[i].ne){
            auto [v,c,w,_]=e[i];
            if(dis[v]>dis[u]+w&&c){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    vis[v]=true;
                    // SLF optimization: If the new distance is less than the front-of-queue distance, insert at the front of the queue.
                    if(!q.empty()&&dis[v]<dis[q.front()]){
                        q.push_front(v);
                    }else{
                        q.push_back(v);
                    }
                }
            }
        }
    }
    return dis[snk]<INF; 
}

ll dfs(ll u,ll mf){
    if(u==snk) return mf;
    ll res=0;
    vis[u]=true;
    for(ll i=cur[u];i;i=e[i].ne){
        cur[u]=i; 
        auto [v,c,w,_]=e[i];
        if(!vis[v]&&dis[v]==dis[u]+w&&c){
            ll f=dfs(v,min(mf,c));
            if(f){
                e[i].c-=f;
                e[i^1].c+=f;
                res+=f;
                mf-=f;
                cost+=f*e[i].w;
                if(mf==0) break;
            }
            else{
                dis[v]=INF; 
            }
        }
    }
    vis[u]=false; 
    return res;
}

void dinic(){
    while(spfa()){
        flow+=dfs(src,INF);
    }
}

void solve(){
    cin>>n>>m>>src>>snk;
    for(ll i=1;i<=m;i++){
        ll u,v,c,w;
        cin>>u>>v>>c>>w;
        add_edge(u,v,c,w);
        add_edge(v,u,0,-w); // 反向边
    }
    
    dinic();
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