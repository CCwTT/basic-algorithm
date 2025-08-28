//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1009
//@@@
//math,__int128,the property of multiplicative inverse
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

ll p0;
i128 p,k;

i128 qpow(i128 x,i128 n){
    i128 res=1;
    while(n){
        if(n&1) res=res*x;
        x=x*x;
        n>>=1;
    }
    return res;
}

i128 qpow(i128 x,i128 n,i128 mod){
    i128 res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

i128 inv(i128 x,i128 mod){
    return qpow(x,mod-2,mod);
}

void solve(){
    cin>>p0;
    p=p0;
    k=(p+118)/119;
    if(k<23){
        i128 ans=0;
        for(i128 i=1;i<p;i++){
            i128 cur=(inv(i,p)+qpow(2,k))*(i+qpow(4,k));
            ans=ans^cur;
        }
        cout<<(ll)(ans%MOD)<<endl;
    }else{
        i128 tmp=0;
        for(ll i=p-1-(p-1)%4;i<p;i++){
            tmp=tmp^i;
        }
        i128 ans=(1^(p-1)*(p-1))+((qpow(4,k,MOD)+qpow(2,k,MOD))*tmp%MOD);
        cout<<(ll)(ans%MOD)<<endl;
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