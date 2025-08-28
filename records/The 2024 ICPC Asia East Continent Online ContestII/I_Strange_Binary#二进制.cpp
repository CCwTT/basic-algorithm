//https://qoj.ac/contest/1799/problem/9378
//@@@
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

void solve(){
    ll n;
    cin>>n;
    if(n%4==0){
        cout<<"NO"<<endl;
        return;
    }
    bool flag=0;
    if(~n&1){
        n++;
        flag=1;
    }
    vector<ll> v(32,-1);
    for(ll i=31;i>=0;i--){
        if((n>>(i+1)&1)||i==31){
            v[i]=1;
        }
    }
    if(flag){
        v[0]=0;
    }
    cout<<"YES"<<endl;
    for(ll i=0;i<32;i++){
        cout<<v[i]<<" ";
        if(i%8==7) cout<<endl;
    }
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