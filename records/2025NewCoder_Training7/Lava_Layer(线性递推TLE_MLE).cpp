//TLE/MLE线性递推代码
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
const ll mod=998244353;
ll p,K;
ll D[N];

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

ll inv(ll x){
    return qpow(x,mod-2);
}

void solve(){
    cin>>p>>K;
    for(ll i=1;i<=K;i++){
        cin>>D[i];
    }
    vector<vector<ll>> f(p+1,vector<ll>(16,0));
    vector<vector<ll>> g(p+1,vector<ll>(16,0));
    for(ll l=1;l<=K;l++){
        ll x=D[l];
        f[1][x]++;
    }
    for(ll n=1;n<p;n++){
        for(ll k=0;k<=15;k++){
            for(ll l=1;l<=K;l++){
                ll x=D[l];

                (f[n+1][k+x&15]+=f[n][k])%=mod;
                (g[n+1][k+x&15]+=g[n][k]+(k+x)/16*f[n][k])%=mod;

                (f[n+1][k*x%16]+=f[n][k])%=mod;
                (g[n+1][k*x%16]+=x*g[n][k]+k*x/16*f[n][k])%=mod;

                (f[n+1][k&x]+=f[n][k])%mod;
                
                (f[n+1][k|x]+=f[n][k])%=mod;
                (g[n+1][k|x]+=g[n][k])%=mod;

                (f[n+1][k^x]+=f[n][k])%=mod;
                (g[n+1][k^x]+=g[n][k])%=mod;
            }
        }
    }
    ll fz=0,inv_fm=0;
    for(ll k=0;k<=15;k++){
        (fz+=16*g[p][k]+k*f[p][k])%=mod;
    }
    inv_fm=inv(qpow(5,p-1))*inv(qpow(K,p))%mod;
    cout<<(fz*inv_fm)%mod<<endl;
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