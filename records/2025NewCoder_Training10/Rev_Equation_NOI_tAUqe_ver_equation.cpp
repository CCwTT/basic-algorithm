//https://ac.nowcoder.com/acm/contest/108307/H
//@@@
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
    string s;
    cin>>s;
    if(s[0]==s[2]){
        cout<<"No"<<endl;
        return;
    }
    if(s[1]=='-'&&s[0]!='0'){
        cout<<"No"<<endl;
        return;
    }
    cout<<"Yes"<<endl;
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