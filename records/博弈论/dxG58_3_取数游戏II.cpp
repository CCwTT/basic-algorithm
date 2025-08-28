//https://www.luogu.com.cn/problem/P1288
//@@@
//game theory
/*
我们发现如果一方创造出一条0边，另一方如果不复读行为的话，就创造出对方速胜的局面。因此，当一个人创造出一条0边的时候，两人就必须沿着既定方向狂奔，一直到撞到一条0边。

那么，当甲先手时，如果他到两个其中一个端点（端点为可移动范围的两端）的距离为奇数条边的时候，他可以选择向其进入狂奔，必胜，因为最后一条边一定是甲取。

反之，如果两个距离都是偶数，那么如果甲开始狂奔，那么输，如果甲不创造零边，那么给乙创造出两奇数必胜的局面。
考察先手位置到两端点的距离大小的奇偶性即可。

We found that if one side creates a 0 - edge, and the other side does not repeat the behavior, it will create a situation where the opponent can win quickly. Therefore, when a person creates a 0 - edge, the two must run along the established direction until they hit a 0 - edge.

So, when Player A moves first, if the distance from him to one of the two endpoints (the endpoints are the two ends of the movable range) is an odd number of edges, he can choose to enter a wild run towards it and will surely win, because Player A will definitely take the last edge.

Conversely, if both distances are even, then if Player A starts a wild run, he will lose. If Player A does not create a zero - edge, it will create a situation where Player B has two odd - distance positions and can win. It is only necessary to examine the parity of the size of the distances from the starting position of the first - mover to the two endpoints.
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
    vector<ll> a(n);
    for(ll i=0;i<n;i++) cin>>a[i];
    ll cnt1=0,cnt2=0;
    for(ll i=0;i<n;i++){
        if(a[i]) cnt1++;
        else break;
    }
    for(ll i=n-1;i>=0;i--){
        if(a[i]) cnt2++;
        else break;
    }
    if((cnt1&1)||(cnt2&1)){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}