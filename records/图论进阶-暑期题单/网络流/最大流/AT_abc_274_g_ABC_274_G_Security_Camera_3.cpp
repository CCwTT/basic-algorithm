//https://atcoder.jp/contests/abc274/tasks/abc274_g
//@@@
//maximum flow,Konig theorem
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

struct network_flow{
    struct edge{
        ll to,c,ne;
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
        e.resize((m+1)<<1);
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

    ll max_flow(ll src,ll snk){
        this->src=src,this->snk=snk;
        ll flow=0;
        while(bfs()){
            cur=h;
            flow+=dfs(src,INF);
        }
        return flow;
    }
};


void solve(){
    ll n,m;
    cin>>n>>m;
    vector grid(n+1,vector<char>(m+1));
    vector bel_h(n+1,vector<ll>(m+1));
    vector bel_v(n+1,vector<ll>(m+1));
    ll cnt_h=0,cnt_v=0;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cin>>grid[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1,k=1;j<=m;j=k) {
            if(grid[i][j]=='.'){
                ++cnt_h;
                while(k<=m&&grid[i][k]=='.') bel_h[i][k++]=cnt_h;
            }else{
                while(k<=m&&grid[i][k]=='#') k++;
            }
        }
    }
    for(ll j=1;j<=m;j++){
        for(ll i=1,k=1;i<=n;i=k){
            if(grid[i][j]=='.'){
                ++cnt_v;
                while(k<=n&&grid[k][j]=='.') bel_v[k++][j]=cnt_v;
            }else{
                while(k<=n&&grid[k][j]=='#') k++;
            }
        }
    }
    network_flow flow(cnt_h+cnt_v+2,3*n*m+5);
    ll src=0,snk=cnt_h+cnt_v+1;
    for(ll i=1;i<=cnt_h;i++){
        flow.add_edge(src,i,1);
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++) if(grid[i][j]=='.'){
            flow.add_edge(bel_h[i][j],cnt_h+bel_v[i][j],1);
        }
    }
    for(ll i=1;i<=cnt_v;i++){
        flow.add_edge(cnt_h+i,snk,1);
    }
    cout<<flow.max_flow(src,snk)<<endl;

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