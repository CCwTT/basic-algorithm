//https://qoj.ac/contest/1799/problem/9376
//@@@
//dfs
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

const ll MOD=998244353;
ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%MOD;
        x=x*x%MOD;
        n>>=1;
    }
    return res;
}

ll inv(ll x){
    return qpow(x,MOD-2);
}

//x<=y
ll f(ll x,ll y,ll px,ll py){
    if(x==0) return 0;
    return qpow(px,y/x)*((1-f(y%x,x,py,px)+MOD)%MOD)%MOD;
}

void solve(){
    ll x,y;
    cin>>x>>y;
    ll a0,a1,b;
    cin>>a0>>a1>>b;
    ll p0=a0*inv(b)%MOD;
    ll p1=a1*inv(b)%MOD;
    tie(p0,p1)=tuple{p0*inv(p0+p1)%MOD,p1*inv(p0+p1)%MOD};
    if(x<=y){
        cout<<f(x,y,p0,p1)<<endl;
    }else{
        cout<<(1-f(y,x,p1,p0)+MOD)%MOD<<endl;
    }
}

void clear(){}

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