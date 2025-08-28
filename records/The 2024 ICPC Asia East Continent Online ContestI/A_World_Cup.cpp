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

const ll N=40;
ll a[N];

void solve(){
    for(ll i=1;i<=32;i++){
        cin>>a[i];
    }
    ll rk=32;
    for(ll i=2;i<=32;i++){
        if(a[1]>a[i]){
            rk--;
        }
    }
    rk=32+1-rk;
    ll ans=0;
    if(rk<=2) ans=32;
    else if(rk<7) ans=16;
    else if(rk<14) ans=8;
    else if(rk<28) ans=4;
    else if(rk<32) ans=2;
    else ans=1;
    cout<<ans<<endl;
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