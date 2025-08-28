//https://ac.nowcoder.com/acm/contest/108306/G
//@@@
//Cartesian tree,partition method
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

constexpr ll N=2e6+10,MOD=998244353;
ll n,a[N];
ll lc[N],rc[N];
ll stk[N];
ll dep[N],siz[N],res;
ll fac[N],inv_fac[N];

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%MOD;
        x=x*x%MOD;
        n>>=1;
    }
    return res;
}

ll init=[](){
    fac[0]=inv_fac[0]=1;
    for(ll i=1;i<N;i++) fac[i]=fac[i-1]*i%MOD;
    inv_fac[N-1]=qpow(fac[N-1],MOD-2);
    for(ll i=N-2;i;i--) inv_fac[i]=inv_fac[i+1]*(i+1)%MOD;
    return 0;
}();

ll C(ll n,ll m){
    if(n<0||n<m) return 0;
    return fac[n]*inv_fac[m]%MOD*inv_fac[n-m]%MOD;
}

void build(){
    ll top=0;
    for(ll i=1;i<=n;i++){
        ll p=top;
        while(p&&a[stk[p]]>a[i]) p--;
        if(p) rc[stk[p]]=i;
        if(p<top) lc[i]=stk[p+1];
        stk[++p]=i;
        top=p;
    }
}

void dfs(ll u,ll fa){
    if(u==0) return;
    dep[u]=dep[fa]+1;
    dfs(lc[u],u);
    dfs(rc[u],u);
    siz[u]=siz[lc[u]]+siz[rc[u]]+1;
    res=(res+C(siz[u]+dep[u]-1,siz[u]-1))%MOD;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    memset(lc,0,sizeof(ll)*(n+10));
    memset(rc,0,sizeof(ll)*(n+10));
    build();
    res=0;
    dfs(stk[1],0);
    cout<<res+1<<endl;
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