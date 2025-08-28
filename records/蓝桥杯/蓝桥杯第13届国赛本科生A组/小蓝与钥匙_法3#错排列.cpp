////https://www.lanqiao.cn/problems/2167/learning/
//@@@
//combination number,derrangement
//D(n)=(n-1)*(D(n-1)+D(n-2))
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

ll fac[15];
ll C[30][15];
ll D[15];
ll init=[]{
    fac[0]=fac[1]=1;
    for(ll i=2;i<15;i++){
        fac[i]=fac[i-1]*i;
    }
    for(ll i=0;i<30;i++){
        C[i][0]=1;
    }
    for(ll i=1;i<30;i++){
        for(ll j=1;j<=min(14ll,i);j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1]);
        }
    }
    D[0]=1;
    D[1]=0;
    for(ll i=2;i<15;i++){
        D[i]=(i-1)*(D[i-1]+D[i-2]);
    }
    return 0;
}();

void solve(){
    cout<<C[28][14]*D[14]<<endl;
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