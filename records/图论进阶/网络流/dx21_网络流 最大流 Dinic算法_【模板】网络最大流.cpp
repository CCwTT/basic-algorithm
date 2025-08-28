//https://www.luogu.com.cn/problem/P3376
//@@@
//maximum flow(dinic)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

struct network_flow{
	const static ll MAXN=1e5+5;
	const static ll MAXM=2e6+5;
    struct edge{
        ll to,c,ne;
    };

    ll n,m;
    edge e[MAXM]; ll h[MAXN]; ll cnte=1;
    ll dep[MAXN],cur[MAXN];
    ll src,snk;

    network_flow(ll n=0){
		clear();
        this->n=n;
    }

    void clear(){
		for(ll i=0;i<=n;i++){
			h[i]=dep[i]=cur[i]=0;
		}
		for(ll i=0;i<=cnte;i++){
			e[i]={0,0,0};
		}
		cnte=1;
		src=snk=0;
	}

    void add_edge(ll u,ll v,ll c){
        e[++cnte]={v,c,h[u]};
        h[u]=cnte;
        e[++cnte]={u,0,h[v]};
        h[v]=cnte;
    }

    bool bfs(){
        fill(dep,dep+n+1,0);
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
            copy(h,h+n+1,cur);
            flow+=dfs(src,INF);
        }
        return flow;
    }
};

void solve(){
	ll n,m,src,snk;
    cin>>n>>m>>src>>snk;
	network_flow flow(n+m+2);
    for(ll i=1;i<=m;i++){
        ll u,v,c;
        cin>>u>>v>>c;
        flow.add_edge(u,v,c);
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