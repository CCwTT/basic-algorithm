//https://www.luogu.com.cn/problem/P3254
//@@@
//maximum bipartite matching(Dinic algorithm)
//O(n^0.5m)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1005,M=1e5+5;

struct network_flow{
    struct edge{
        ll to,cap,ne;
    };

    ll n,m;
    vector<edge> e; vector<ll> h; ll cnte=1;
    vector<ll> dep,cur;
    ll src,snk;

    network_flow(ll n=0,ll m=0){
        init(n,m);
    }

    void init(ll n,ll m){
        n=n,m=m;
        e.resize((m<<1)+5);
        h.resize(n+1);
        dep.resize(n+1);
        cur.resize(n+1);
        cnte=1;
    }

    void add_edge(ll u,ll v,ll c){
        e[++cnte]={v,c,h[u]};
        h[u]=cnte;
        e[++cnte]={u,0,h[v]};
        h[v]=cnte;
    }

    bool bfs(){
        fill(dep.begin(),dep.end(),0);
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
                e[i].cap-=f;
                e[i^1].cap+=f;
                res+=f;
                mf-=f;
                if(mf==0) break;
            }
        }
        if(res==0) dep[u]=0;
        return res;
    }

    ll max_flow(ll src,ll snk){
        this->src=src,this->snk=snk;
        ll flow=0;
        while(bfs()){
            cur=h;
            flow+=dfs(src,inf);
        }
        return flow;
    }
};

void solve(){
    ll m,n,src,snk;
    cin>>m>>n;
    network_flow flow(N,M);
    vector<ll> a(m+1),b(n+1);
    for(ll i=1;i<=m;i++) cin>>a[i];
    for(ll i=1;i<=n;i++) cin>>b[i];
    src=0;snk=m+n+1;
    for(ll i=1;i<=m;i++){
        flow.add_edge(src,i,a[i]);
        for(ll j=1;j<=n;j++){
            flow.add_edge(i,m+j,1);
        }
    }
    for(ll i=1;i<=n;i++){
        flow.add_edge(m+i,snk,b[i]);
    }
    ll ret=flow.max_flow(src,snk);
    if(ret!=accumulate(a.begin()+1,a.end(),0ll)){
        cout<<0<<endl;
        return;
    }
    cout<<1<<endl;
    for(ll i=1;i<=m;i++){
        for(ll j=flow.h[i];j;j=flow.e[j].ne){
            auto [to,w,ne]=flow.e[j];
            if(to!=src&&w==0){
                cout<<to-m<<" ";
            }
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