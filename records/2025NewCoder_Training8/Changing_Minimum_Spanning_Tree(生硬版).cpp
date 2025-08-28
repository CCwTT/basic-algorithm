//https://ac.nowcoder.com/acm/contest/108305/G
//@@@
//graph theory,heuristic merging
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,4> al4;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll MOD=1e9+7;
ll n,m,K;
const ll N=1e5+5;
const ll M=2e5+5;

struct disjoint_set_union{
    ll f[N],siz[N];
    void init(ll n){
        for(ll i=0;i<=n;i++){
            f[i]=i;
            siz[i]=1;
        }
    }
    ll find(ll x){
        return f[x]==x?x:f[x]=find(f[x]);
    }
    void join(ll x,ll y){
        ll fx=find(x),fy=find(y);
        if(fx==fy) return;
        siz[fx]+=siz[fy];
        f[fy]=fx;
    }
    bool check(ll x,ll y){
        return find(x)==find(y);
    }
}dsu;

bool vis[M];

void solve(){
    cin>>n>>m>>K;
    fill(vis,vis+m+1,false);
    dsu.init(n);
    vector<ll> g[n+1];
    vector<al3> g0[n+1];
    vector<al4> edges={{-1,-1,-1,-1}};
    vector<ll> tmp;
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g0[u].push_back({w,v,i});
        g0[v].push_back({w,u,i});
        edges.push_back({w,u,v,i}); //////
        dsu.join(u,v);
    }
    ll component=0;
    for(ll i=1;i<=n;i++){
        if(dsu.find(i)==i){
            component++;
            tmp.push_back(dsu.siz[i]);
        }
    }
    if(component>2){
        cout<<0<<endl;
        return;
    }
    if(component==2){
        cout<<tmp[0]*tmp[1]%MOD*K%MOD<<endl;
        return;
    }
    dsu.init(n);
    sort(edges.begin(),edges.end());
    ll cw=1,dashed=m,ans=0,sum=0;
    for(ll i=1,j=1;i<=m;i=j){
        while(j<=m&&edges[j][0]==edges[i][0]) j++;
        (ans+=(n*(n-1)/2-sum-dashed)%MOD*(edges[i][0]-cw))%=MOD;
        cw=edges[i][0];
        for(ll k=i;k<j;k++){
            auto [w,u,v,id]=edges[k];
            if(vis[id]) continue;
            ll fu=dsu.find(u);
            ll fv=dsu.find(v);
            if(fu==fv) continue;

            function<void(ll,ll,ll,ll)> dfs=[&](ll x,ll fthis,ll fthat,ll w0)->void{
                for(auto [w,y,id]:g0[x]){
                    ll fy=dsu.find(y);
                    for(auto y:g[x]){
                        dfs(y,fthis,fthat,w0);
                    }
                    if(!vis[id]&&fy==fthat){
                        vis[id]=true;
                        dashed--;
                    }
                }
            };

            ll sizu=dsu.siz[fu];
            ll sizv=dsu.siz[fv];
            ll sz=sizu+sizv;
            (sum+=-sizu*(sizu-1)/2-sizv*(sizv-1)/2+sz*(sz-1)/2)%=MOD;
            if(dsu.siz[fu]<dsu.siz[fv]){
                swap(fu,fv);
            }
            dfs(fv,fv,fu,w);
            dsu.join(fu,fv);
            g[fu].push_back(fv);
        }
    }
    cout<<(ans+MOD)%MOD<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}

/*
1
5 4 6
1 2 2


5 3 4
5 4 4
3 4 5
*/