//https://www.luogu.com.cn/problem/P2762
//@@@
//minimum cut,sscanf
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

ll n,m;

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
            flow+=dfs(src,INF);
        }
        return flow;
    }
};


void solve(){
    cin>>n>>m;
    network_flow flow(2+n+m,n+m+n*m);
    vector<ll> p(n+1),c(m+1);
    for(ll i=1;i<=n;i++){
        scanf("%lld",p.begin()+i);
        char tools[10000];
        memset(tools,0,sizeof tools);
        cin.getline(tools,10000);
        ll ulen=1,tool;
        while(sscanf(tools+ulen,"%lld",&tool)==1){
            flow.add_edge(i,tool+n,INF);
            if(tool==0){
                ulen++;
            }else{
                while(tool){
                    tool/=10;
                    ulen++;
                }
            }
            ulen++;
        }
        flow.add_edge(0,i,p[i]);
    }
    for(ll i=1;i<=m;i++){
        cin>>c[i];
        flow.add_edge(i+n,n+m+1,c[i]);
    }
    ll ans=accumulate(p.begin()+1,p.end(),0ll)-flow.max_flow(0,n+m+1);
    for(ll i=1;i<=n;i++){
        if(flow.dep[i]){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    for(ll i=1;i<=m;i++){
        if(flow.dep[i+n]){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    cout<<ans<<endl;
}

void clear(){

}

signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}