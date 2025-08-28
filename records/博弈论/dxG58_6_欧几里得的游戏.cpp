//https://www.luogu.com.cn/problem/P1290
//@@@
//game theory
//(1)题目等价于，有n堆石子，每次从最前面一堆中取走任意个石子，先取完第一堆才能取第二堆，取完第二堆才能取第三堆...，取走最后一堆的最后一个石子的人获胜 (2)若每堆石子个数都大于1，则对于前n-1堆石子，先手取后都剩下一个石子，后手只能取剩下的一颗石子，从而先手能一次性取走最后一堆石子 (3)以连续的只有1颗石子的石子堆为分界将n堆石子分为若干段，假设第一堆石子不止1颗，则先手可以保证在每一段都是先手，从而取胜 (4)假设前x堆石子只有1颗石子，第(x+1)堆石子越界或不止1颗石子，则x是偶数时，先手必胜；x是奇数时，相当于先后手翻转，后手必胜
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
    ll x,y;
    cin>>x>>y;
    if(x==y){
        cout<<"Stan wins"<<endl;
        return;
    }
    if(x<y) swap(x,y);
    ll cnt=0;
    while(y!=0){
        if(x<y*2) cnt++;
        else break;
        x%=y;
        swap(x,y);
    }
    cout<<(~cnt&1?"Stan wins":"Ollie wins")<<endl;
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