//https://www.luogu.com.cn/problem/P1247
//@@@
//game theory
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

const ll N=5e5+5;
ll a[N];
ll n;

void solve(){
    cin>>n;
    ll XOR=0;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        XOR^=a[i];
    }
    if(!XOR){
        cout<<"lose"<<endl;
    }else{
        for(ll i=1;i<=n;i++){
            if((a[i]^XOR)<a[i]){
                cout<<(a[i]-(a[i]^XOR))<<" "<<i<<endl;
                a[i]^=XOR;
                break;
            }
        }
        for(ll i=1;i<=n;i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
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