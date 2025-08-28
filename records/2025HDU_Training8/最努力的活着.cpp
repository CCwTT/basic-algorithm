//https://acm.hdu.edu.cn/contest/status?cid=1179&rid=13778
//@@@
//__int128
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef  __int128 i128;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

ostream &operator<<(ostream &os, __int128 x){
    string s;
    ll sign=1;
    if(x<0){
      sign=-1;
      x=-x;
    }
    if(x==0) s="0";
    while(x){
        s+=x%10+'0';
        x/=10;
    }
    if(sign==-1) s+='-';
    reverse(s.begin(), s.end());
    return os<<s;
}

istream &operator>>(istream &is, __int128 &x){
    string s;
    cin>>s;
    x=0;
    ll sign=1;
    ll i=0;
    if(s[0]=='-'){
      sign=-1;
      i=1;
    }
    for(;i<s.size();i++){
      x=x*10+(s[i]-'0');
    }
    x*=sign;
    return is;
}

i128 n,w;

void solve(){
    cin>>n>>w;
    i128 n0=n;
    i128 res=0;
    i128 it=1;
    while(w*w<=n){
        res+=(it+n0)*(n0-it+1)/2;
        i128 m=n/w;
        n-=m;
        it+=m;
    }
    while(w<=n){
        i128 m=n/w;
        i128 t=m*w-1;
        i128 c=(n-t+m-1)/m;
        i128 add=0;
        add+=c*(n0+it)*(n0-it+1);
        add+=c*(c-1)/2*(-2*it+1)*m;
        add-=c*(c-1)*(2*c-1)/6*m*m;
        res+=add/2;
        n-=m*c;
        it+=m*c;
    }
    res+=(it+n0)*(n0-it+1)/2;
    cout<<res<<endl;
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