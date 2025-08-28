//https://acm.hdu.edu.cn/contest/problem?cid=1178&pid=1002
//@@@
//ternary search
//link:records\2025HDU_Training7\龙族栖息地.cpp
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

const ll N=1e5+5;
ll q[N],r[N],s[N];
ll n;

ll f(ll x,ll y){
    ll res=0;
    for(ll i=1;i<=n;i++){
        res+=abs(x-q[i])+abs(y-r[i])+abs(-x-y-s[i]);
    }
    return res;
}

ll check(ll x){
    vector<ll> tab;
    for(ll i=1;i<=n;i++){
        tab.push_back(r[i]);
        tab.push_back(-x-s[i]);
    }
    nth_element(tab.begin(),tab.begin()+tab.size()/2,tab.end());
    return f(x,tab[tab.size()/2]);
}

void solve(){
    cin>>n;
    ll ans=INF;
    for(ll i=1;i<=n;i++){
        cin>>q[i]>>r[i]>>s[i];
    }
    ll l=-1e9-10,r=1e9+10,x;
    while(l<=r){
        ll m1=l+(r-l)/3,m2=r-(r-l)/3;
        //ll m1=max(l,l+r-1>>1),m2=min(r,l+r+1>>1); //二分化三分
        if(check(m1)>check(m2)){
            x=m2;
            l=m1+1;
        }else{
            x=m1;
            r=m2-1;
        }
    }
    cout<<check(x)/2<<endl;
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