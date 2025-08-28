//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1001
//@@@
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=10;
ll a[N];

void solve(){
    for(ll i=0;i<N;i++) cin>>a[i];
    ll ans=a[0]+a[4]+a[8];
    ll sum69=a[9]+a[6];
    a[9]+=a[6];
    a[6]=0;
    ll oddsum=a[1]+a[3]+a[5]+a[7]+a[9];
    ll b=min(a[2],oddsum);
    ans+=b;
    ll restodd=oddsum-b;
    ll rest69=min(restodd,sum69);
    ll rest135=restodd-rest69;
    ll c=min(rest69,rest135);
    ans+=c;
    rest69-=c;
    ans+=rest69/2;
    cout<<ans<<endl;
}

void clear(){

}

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