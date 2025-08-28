//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1001
//@@@
//game theory
//反尼姆游戏(取走最后一颗石子的人失败):
//1.当每堆石子的数量都为1时,异或和为0时先手获胜;
//2.当有至少一堆石子的个数大于1时,异或和不为0时先手获胜。
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MX=1e6+5;
const ll mod=1e9+7;
ll fac[MX],inv_fac[MX];

ll qpow(ll x,ll n){
    if(x==0) return 0;
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

ll init=[]{
    fac[0]=1;
    for(ll i=1;i<MX;i++){
        fac[i]=fac[i-1]*i%mod;
    }
    inv_fac[MX-1]=qpow(fac[MX-1],mod-2);
    for(ll i=MX-2;i>=0;i--){
        inv_fac[i]=inv_fac[i+1]*(i+1)%mod;
    }
    return 0;
}();

ll C(ll n,ll m){
    if(n<0||n<m) return 0;
    return fac[n]*inv_fac[m]%mod*inv_fac[n-m]%mod;
}

ll A(ll n,ll m){
    if(n<0||n<m) return 0;
    return fac[n]*inv_fac[n-m]%mod;
}

void solve(){
    ll n;
    cin>>n;
    ll cnt=0;
    ll c0=0,c1=0,c2=0,c3=0;
    for(ll i=1;i<=n;i++){
        ll k;
        cin>>k;
        ll XOR=0;
        bool ok=true;
        for(ll j=1;j<=k;j++){
            ll x;
            cin>>x;
            if(x>1){
                ok=false;
            }
            XOR^=x;
        }
        cnt+=k;
        if(ok){
            if(XOR) c1++;
            else c0++;
        }else{
            if(XOR) c3++;
            else c2++;
        }
    }
    if(c2+c3==0){
        if(c1&1){
            cout<<fac[n]<<endl;
        }else{
            cout<<0<<endl;
        }
        return;
    }
    ll ans=0;
    for(ll i=0;i<=c1;i++){
        if(i&1){
            ans+=A(c1,i)*c2%mod*fac[c2+c3-1+c1-i]%mod;
            ans%=mod;
        }else{
            ans+=A(c1,i)*c3%mod*fac[c2+c3-1+c1-i]%mod;
            ans%=mod;
        }
    }
    ans=ans*A(n,c0)%mod;
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}