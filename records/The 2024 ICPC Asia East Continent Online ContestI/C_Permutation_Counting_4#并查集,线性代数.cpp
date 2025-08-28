//https://qoj.ac/contest/1794/problem/9310
//@@@
//dsu,linear algebra
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

const ll N=1e6+5;
ll l[N],r[N];
ll f[N];

ll find(ll x){
    return f[x]==x?x:f[x]=find(f[x]);
}

void solve(){
    ll n;
    cin>>n;
    iota(f+1,f+n+2,1);
    for(ll i=1;i<=n;i++){
        cin>>l[i]>>r[i];
    }
    for(ll i=1;i<=n;i++){
        if(find(l[i])==find(r[i]+1)){
            cout<<0<<endl;
            return;
        }
        f[find(l[i])]=find(r[i]+1);
    }
    cout<<1<<endl;
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