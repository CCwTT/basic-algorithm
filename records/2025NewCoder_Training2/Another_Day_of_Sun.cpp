#include <bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

const ll MAXN=5e5+5;
ll mod=998244353;
ll n;
ll a[MAXN];

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=(res*x)%mod;
        x=(x*x)%mod;
        n>>=1;
    }
    return res;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<vector<ll>> f(n+1,vector<ll>(2,0));
    ll cnt=0;
    for(ll i=1;i<=n;i++){
        if(a[i-1]==1){
            if(a[i]==0){
               f[i][0]=f[i-1][1]; 
            }else if(a[i]==1){
                f[i][1]=f[i-1][1];
            }else{
                f[i][0]=f[i][1]=f[i-1][1];
            }
        }else if(a[i-1]==0){
            if(a[i]==0){
                f[i][0]=f[i-1][0];
            }else if(a[i]==1){
                f[i][1]=(f[i-1][0]+qpow(2,cnt))%mod;
            }else{
                f[i][0]=f[i-1][0];
                f[i][1]=(f[i-1][0]+qpow(2,cnt))%mod;
            }
        }else{
            if(a[i]==0){
                f[i][0]=(f[i-1][0]+f[i-1][1])%mod;
            }else if(a[i]==1){
                f[i][1]=(f[i-1][0]+qpow(2,cnt)+f[i-1][1])%mod;
            }else{
                f[i][0]=(f[i-1][0]+f[i-1][1])%mod;
                f[i][1]=(f[i-1][0]+qpow(2,cnt)+f[i-1][1])%mod;
            }
            cnt++;
        }
    }
    cout<<(~a[n]?f[n][a[n]]:(f[n][0]+f[n][1])%mod)<<endl;
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