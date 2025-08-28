//https://www.lanqiao.cn/problems/2167/learning/
//@@@
//combination number,dp
//超大质数是LLONG_MAX-24
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


const ll MOD=9223372036854775783;
ll qpow(ll x,ll n){
    if(x==0) return 0;
    ll res=1;
    while(n){
        if(n&1) res=(i128)res*x%MOD;
        n>>=1;
        x=(i128)x*x%MOD;
    }
    return res;
}

const ll MX=2e6+5;
ll fac[MX],inv_fac[MX];
int init=[]{
    fac[0]=1;
    for(ll i=1;i<MX;i++){
        fac[i]=(i128)fac[i-1]*i%MOD;
    }
    inv_fac[MX-1]=qpow(fac[MX-1],MOD-2);
    for(ll i=MX-2;i>=0;i--){
        inv_fac[i]=(i128)inv_fac[i+1]*(i+1)%MOD;
    }
    return 0;
}();

ll C(ll n,ll m){
    if(m<0||n<m) return 0;
    return (i128)fac[n]*inv_fac[m]%MOD*inv_fac[n-m]%MOD;
}

ll f[20];

void solve(){
    f[0]=1;
    for(ll i=1;i<=14;i++){
        for(ll j=1;i-j>=1;j++){
            f[i]+=C(i-1,j)*fac[j]*f[i-j-1];
        }
    }
    cout<<C(28,14)*f[14]<<endl;
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