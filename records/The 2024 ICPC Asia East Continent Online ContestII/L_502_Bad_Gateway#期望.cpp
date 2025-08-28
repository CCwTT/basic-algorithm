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

pll get_E(ll x,ll T){
    ll fz=x*(x-1)+2*T;
    ll fm=2*x;
    ll g=gcd(fz,fm);
    return {fz/g,fm/g};
}

void solve(){
    ll T;
    cin>>T;
    ll x1=floor(sqrt(2*T));
    ll x2=ceil(sqrt(2*T));
    auto [fz1,fm1]=get_E(x1,T);
    auto [fz2,fm2]=get_E(x2,T);
    if(fz1*fm2<=fz2*fm1){
        cout<<fz1<<" "<<fm1<<endl;
    }else{
        cout<<fz2<<" "<<fm2<<endl;
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