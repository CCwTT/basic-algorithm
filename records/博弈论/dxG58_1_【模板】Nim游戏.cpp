//https://www.luogu.com.cn/problem/P2197
//@@@
//game theory
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

void solve(){
    ll n;
    cin>>n;
    ll XOR=0;
    for(ll i=0;i<n;i++){
        ll x;
        cin>>x;
        XOR^=x;
    }
    cout<<(XOR?"Yes":"No")<<endl;
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