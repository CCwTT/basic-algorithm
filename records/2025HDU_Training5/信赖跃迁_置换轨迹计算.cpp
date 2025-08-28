//https://acm.hdu.edu.cn/contest/problem?cid=1176&pid=1004
//@@@
//i dont know
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
const ll mod=1e9+7;
ll n,m,q[N],k[N];
ll fac[N];

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

int init=[]{
    fac[0]=1;
    for(ll i=1;i<N;i++){
        fac[i]=fac[i-1]*i%mod;
    }
    return 0;
}();

void solve(){
    cin>>n>>m;
    for(ll i=0;i<n;i++){
        cin>>q[i];
    }
    for(ll i=0;i<m;i++){
        cin>>k[i];
    }
    cout<<qpow(fac[n],m)<<endl;
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