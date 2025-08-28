//https://www.luogu.com.cn/problem/P4279
//@@@
//game theory(anti-Nim game)
/*
若每堆石子都只有一颗，则n为偶数时先手胜，奇数时后手胜
否则，每堆石子数量的异或和XOR大于0时先手胜，XOR为0后手胜(此时同Nim游戏)
If each pile of stones has only one stone, the first player wins when n is even, and the second player wins when n is odd. Otherwise, when the XOR sum of the number of stones in each pile is greater than 0, the first player wins, and when the XOR sum is 0, the second player wins (this is the same as the Nim game at this time).
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
    ll cnt=0,XOR=0;
    for(ll i=0;i<n;i++){
        cin>>a[i];
        cnt+=a[i]>1;
        XOR^=a[i];
    }
    if(cnt==0){
        cout<<(n&1?"Brother":"John")<<endl;
        return;
    }
    cout<<(XOR?"John":"Brother")<<endl;
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