//https://ac.nowcoder.com/acm/contest/108306/M
//@@@
/*
当n<10的时候，a=1为其中一个解；否则，可以证明无解：
首先,S(a+b)≤S(a)+S(b),等号成立当且仅当加法的过程中没有进位。
所以,S(na)≤S(a)+···+S(a),即n个a相加的时候不发生进位。然而,a的十进制最高位在加了≥10次之后必然会进位。
因此,在n≥10时,S(na)=nS(a)不可能成立。
*/
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

void solve(){
    ll n;
    cin>>n;
    cout<<(n>=10?-1:1)<<endl;
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