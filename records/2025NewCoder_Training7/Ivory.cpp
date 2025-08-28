//https://ac.nowcoder.com/acm/contest/108304/J
//KNOWLEDGE:若gcd(a,b)=1,则gcd(a,b*c)=gcd(a,c)
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

const ll MOD=998244353;
ll a,b,c,d;

ll qpow(ll x,ll n){
    x%=MOD;
    ll res=1;
    while(n){
        if(n&1) res=res*x%MOD;
        x=x*x%MOD;
        n>>=1;
    }
    return res;
}

ll f(){
    if(gcd(a,c)==1) return 1;
    if(b==d){
        return qpow(gcd(a,c),b);
    }
    if(b>d){
        swap(a,c);
        swap(b,d);
    }
    ll g=gcd(a,c);
    a/=g;
    d-=b;
    return f()*qpow(g,b)%MOD;
}

void solve(){
    cin>>a>>b>>c>>d;
    cout<<f()<<endl;
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