//https://www.luogu.com.cn/problem/P1344
//@@@
//minimum cut
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=10005;
const ll M=2e5+5;

ll n,m,src,snk;
struct edge{ll to,c,ne;}e[M];
ll h[N],cnte=1;
ll dep[N],cur[N];
bool vis[N];

ll u[N],v[N],c;

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
            ll v=e[i].to;
            if(!dep[v]&&e[i].c){
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
        ll v=e[i].to;
        if(dep[v]==dep[u]+1&&e[i].c){
            ll f=dfs(v,min(mf,e[i].c));
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
    ll res=0;
    while(bfs()){
        memcpy(cur,h,sizeof(h));
        res+=dfs(src,inf);
    }
    return res;
}

void solve(){
    cin>>n>>m;
    src=1,snk=n;
    for(ll i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>c;
        add_edge(u[i],v[i],c);
        add_edge(v[i],u[i],0);
    }
    cout<<dinic()<<" ";
    cnte=1;
    memset(h,0,sizeof(h));
    for(ll i=1;i<=m;i++){
        if(e[2*i].c==0){
            add_edge(u[i],v[i],1);
            add_edge(v[i],u[i],0);
        }else{
            add_edge(u[i],v[i],inf);
            add_edge(v[i],u[i],0);
        }
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