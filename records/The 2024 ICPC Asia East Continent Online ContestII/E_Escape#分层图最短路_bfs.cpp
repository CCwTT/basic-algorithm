//https://qoj.ac/contest/1799/problem/9374
//@@@
//layered graph shortest path,bfs
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

const ll N=2e5+5;
ll n,m,d;
vector<ll> g[N];
ll f[N][2];
bool vis[N][2];
ll from[N][2];

void solve(){
    cin>>n>>m>>d;
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ll num;
    cin>>num;
    queue<pll> q;
    for(ll i=1;i<=num;i++){
        ll x;
        cin>>x;
        q.emplace(x,0);
    }
    while(!q.empty()){
        auto [u,t]=q.front();
        q.pop();
        if(!f[u][t&1]){
            f[u][t&1]=t;
        }
        if(t<d){
            for(auto v:g[u]){
                if(!f[v][t&1^1]){
                    q.emplace(v,t+1);
                }
            }
        }
    }
    vis[1][0]=true;
    from[1][0]=0;
    q.emplace(1,0);
    while(!q.empty()){
        auto [u,t]=q.front();
        q.pop();
        if(u==n){
            cout<<t<<endl;
            ll p=n;
            vector<ll> ans;
            do{
                ans.push_back(p);
                p=from[p][t&1];
                t--;
            }while(p);
            reverse(ans.begin(),ans.end());
            for(auto x:ans){
                cout<<x<<" ";
            }
            cout<<endl;
            return;
        }
        for(auto v:g[u]){
            if(!vis[v][t&1^1]&&(f[v][t&1^1]==0||f[v][t&1^1]>t+1)){
                vis[v][t&1^1]=true;
                from[v][t&1^1]=u;
                q.emplace(v,t+1);
            }
        }
    }
    cout<<-1<<endl;
}

void clear(){
    for(ll i=0;i<=n;i++){
        g[i].clear();
        from[i][0]=from[i][1]=0;
        f[i][0]=f[i][1]=0;
        vis[i][0]=vis[i][1]=false;
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