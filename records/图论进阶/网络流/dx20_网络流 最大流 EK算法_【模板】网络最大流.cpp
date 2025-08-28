//https://www.luogu.com.cn/problem/P3376
//@@@
//maximum flow
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e4+5;
const ll M=2e5+5;

ll n,m,src,snk;
struct Edge{
    ll to,c,ne;
};
Edge e[M];
ll h[N],cnte=1;
ll mf[N],pre[N];

void add_edge(ll u,ll v,ll c){
    e[++cnte]={v,c,h[u]};
    h[u]=cnte;
}

bool bfs(){
    memset(mf,0,sizeof(mf));
    queue<ll> q;
    mf[src]=inf;
    q.push(src);
    while(!q.empty()){
        ll u=q.front();
        q.pop();
        for(ll i=h[u];i;i=e[i].ne){
            ll v=e[i].to;
            if(mf[v]==0&&e[i].c){
                mf[v]=min(mf[u],e[i].c);
                pre[v]=i;
                q.push(v);
                if(v==snk){
                    return true;
                }
            }
        }
    }
    return false;
}

ll EK(){
    ll res=0;
    while(bfs()){
        ll x=snk;
        while(x!=src){
            ll i=pre[x];
            e[i].c-=mf[snk];
            e[i^1].c+=mf[snk];
            x=e[i^1].to;
        }
        res+=mf[snk];
    }
    return res;
}

void solve(){
    cin>>n>>m>>src>>snk;
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,0);
    }
    cout<<EK()<<endl;
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