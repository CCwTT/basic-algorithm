//https://vjudge.net/contest/729013#problem/B
//@@@
//maximum flow,bipartite graph's edge coloring,Vizing's theorem,ternary search
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
//typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=255;
char grid[N][N];
ll n,m,c,d,cnt_star;

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
}flow;

ll check(ll k){
    ll src=0,snk=n+m+1;
    flow.clear();
    flow.n=n+m+2;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            if(grid[i][j]=='.'){
                flow.add_edge(i,j+n,1);
            }
        }
    }
    for(ll i=1;i<=n;i++){
        flow.add_edge(src,i,k);
    }
    for(ll j=1;j<=m;j++){
        flow.add_edge(j+n,snk,k);
    }
    ll mf=flow.max_flow(src,snk);
    return c*k+d*(n*m-cnt_star-mf);
}

void solve(){
    cin>>n>>m>>c>>d;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cin>>grid[i][j];
            if(grid[i][j]=='*'){
                cnt_star++;
            }
        }
    }
    ll l=0,r=max(n,m),ans;
    while(l<=r){
        ll m1=max(l,(l+r-1)/2);
        ll m2=max(r,(l+r+1)/2);
        ll ret1=check(m1);
        ll ret2=check(m2);
        if(ret1<=ret2){
            ans=ret1;
            r=m2-1;
        }else{
            ans=ret2;
            l=m1+1;
        }
    }
    cout<<ans<<endl;
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}