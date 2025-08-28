//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1002
//@@@
//struct construction,template,Euler's exponent reduction
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

ll qpow(ll x,ll n,ll mod){
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

template<ll mod>
struct am{
    ll l,m,r;
    char op;
    am(ll x=0){
        op='N';
        r=x%mod;
        l=m=0;
    }
    am(ll l_,ll _m,ll r_){
        l=l_%mod; 
        m=_m%mod; 
        r=r_%mod;
        op='C';
    }
    ll result(){
        return (l+m+r)%mod;
    }
};

template<ll mod>
am<mod> operator+(am<mod> a,am<mod> b){
    if(a.op=='N'){
        (b.m+=b.l)%=mod;
        return {a.r,b.m,b.r};
    }
    return {a.l,(a.m+a.r+b.l+b.m)%mod,b.r};
}

template<ll mod>
am<mod> operator*(am<mod> a,am<mod> b){
    if(a.op=='N'&&b.op=='N')
        return {a.r*b.r};
    if(a.op!='N'&&b.op=='N')
        return {a.l,a.m,a.r*b.r};
    if(a.op=='N'&&b.op!='N')
        return {a.r*b.l,b.m,b.r};
    return {a.l,(a.m+a.r*b.l+b.m)%mod,b.r};
}

const ll MOD=1e9+7;
struct lsh{
    am<MOD> l;
    am<MOD-1> r,v;
    bool hasv;
    lsh(ll x=0){
        l=x; 
        r=x; 
        v=0;
        hasv=false;
    }
    lsh(am<MOD> l_,am<MOD-1> r_){
        l=l_; 
        r=r_; 
        v=0;
        hasv=false;
    }
    lsh(am<MOD> l_,am<MOD-1> r_,am<MOD-1> v_){
        l=l_; 
        r=r_; 
        v=v_;
        hasv=true;
    }
    ll result(){
        return l.result()*qpow(2,v.result(),MOD)%MOD;
    }
    am<MOD-1> result_as_right(){
        if(hasv) return r+v;
        return r;
    }
};

lsh operator+(lsh a, lsh b){
    if(a.hasv){
        return {a.l,a.r,a.v+b.result_as_right()};
    }
    if(b.hasv){
        return {a.l+b.l,a.r+b.r, b.v};
    }
    return {a.l+b.l,a.r+b.r};
}

lsh operator*(lsh a,lsh b){
    if(a.hasv){
        return {a.l,a.r,a.v*b.result_as_right()};
    }
    if(b.hasv){
        return {a.l*b.l,a.r*b.r,b.v};
    }
    return {a.l*b.l,a.r*b.r};
}

lsh operator<<(lsh a,lsh b){
    if(a.hasv){
        return {a.l,a.r,a.v+b.result_as_right()};
    }
    return {a.l,a.r,b.result_as_right()};
}

const ll N=3e5+5;

ll n,a[N],b[N];
char typ[N];
lsh dp[N];
bool vis[N];

lsh dfs(ll x){
    lsh& res=dp[x];
    if(vis[x]) return res;
    vis[x]=true;
    if(typ[x]=='N'){
        res=a[x];
    }else if(typ[x]=='<'){
        res=dfs(a[x])<<dfs(b[x]);
    }else if(typ[x]=='+'){
        res=dfs(a[x])+dfs(b[x]);
    }else if(typ[x]=='*'){
        res=dfs(a[x])*dfs(b[x]);
    }   
    return res;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>typ[i];
        if(typ[i]=='N')
            cin>>a[i];
        else cin>>a[i]>>b[i];
    }
    for(ll i=1;i<=n;i++){
        cout<<dfs(i).result()<<endl;
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        memset(dp,-1,sizeof(dp));
        solve();
        clear();
    }
    return 0;
}
