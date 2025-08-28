//https://ac.nowcoder.com/acm/contest/108306/C
//@@@
//state compression,sort,
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

constexpr ll N=30;
ll n,m;
ll a[N],ind[N];
vector<ll> rg(N);
ll dp[1<<N];
ll ans=INF;

ll dfs(ll mask){
    if(mask==(1<<n)-1) return 0;
    ll& res=dp[mask];
    if(res) return res;
    res=INF;
    ll sub=0;
    for(ll i=0;i<n;i++){
        if((~mask>>i&1)&&(rg[i]&mask)==rg[i]){
            sub|=1<<i;
            res=min(res,dfs(mask|sub)+a[i]);
        }
    }
    return res;
}

void solve(){
    cin>>n>>m;
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    vector<ll> id(n);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](ll u,ll v){
        return a[u]<a[v];
    });
    vector<ll> rid(n);
    for(ll i=0;i<n;i++){
        rid[id[i]]=i;
    }
    sort(a,a+n);
    
    for(ll i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        u--,v--;
        u=rid[u];
        v=rid[v];
        rg[v]|=1<<u;
    }
    
    cout<<dfs(0)<<endl;
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