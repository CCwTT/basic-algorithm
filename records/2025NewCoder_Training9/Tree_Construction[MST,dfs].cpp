//https://ac.nowcoder.com/acm/contest/108306/I
//@@@
//MST,dfs
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1010;
ll n,d1[N][N],d2[N][N],e1[N][N],e2[N][N];
vector<pll> ans;

struct disjoint_set_union{
    ll f[N];
    disjoint_set_union(){init();}
    void init(){iota(f,f+N,0);}
    ll find(ll x){
        return f[x]==x?x:f[x]=find(f[x]);
    }
}dsu;

vector<vector<ll>> MST(vector<al3>& edges){
    dsu.init();
    sort(edges.begin(),edges.end());
    vector<vector<ll>> res(n+1,vector<ll>());
    for(auto [w,u,v]:edges){
        ll fu=dsu.find(u);
        ll fv=dsu.find(v);
        if(fu==fv) continue;
        dsu.f[fv]=fu;
        res[u].push_back(v);
        res[v].push_back(u);
        ans.push_back({u,v});
    }
    return res;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            cin>>d1[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            cin>>d2[i][j];
        }
    }
    vector<al3> edges;
    for(ll i=1;i<=n;i++){
        for(ll j=i+1;j<=n;j++){
            edges.push_back({d1[i][j]+d2[i][j],i,j});
        }
    }
    auto g=MST(edges);
    vector<ll> vec;
    function<void(ll,ll)> dfs=[&](ll u,ll fa)->void{
        vec.push_back(u);
        for(auto& v:g[u]) if(v!=fa){
            ll w1=d1[u][v],w2=d2[u][v];
            auto check_and_adjust=[&]()->bool{
                for(auto x:vec){
                    ll t1=e1[x][u]+w1;
                    ll t2=e2[x][u]+w2;
                    if(min(t1,t2)!=min(d1[x][v],d2[x][v])||max(t1,t2)!=max(d1[x][v],d2[x][v])){
                        swap(w1,w2);
                        break;
                    }
                }
                for(auto x:vec){
                    e1[x][v]=e1[v][x]=e1[x][u]+w1;
                    e2[x][v]=e2[v][x]=e2[x][u]+w2;
                }
                return true;
            };
            check_and_adjust();
            dfs(v,u);
        }
    };
    dfs(1,0);
    for(auto [u,v]:ans){
        cout<<u<<" "<<v<<" "<<e1[u][v]<<" "<<e2[u][v]<<endl;
    }
}

void clear(){
    ans.clear();
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            e1[i][j]=e1[j][i]=0;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}
