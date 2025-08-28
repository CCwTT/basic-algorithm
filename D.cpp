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

bool check(vector<ll>& a,vector<ll>& b){
    ll n=a.size();
    for(ll i=0;i<n;i++){
        if(a[i]==b[i]) return false;
    }
    return true;
}

void solve(){
    for(ll n=1;n<=14;n++){
        vector<ll> a(n);
        iota(a.begin(),a.end(),1);
        auto b=a;
        ll cnt=0;
        do{
            if(check(a,b)){
                cnt++;
            }
        }while(next_permutation(b.begin(),b.end()));
        cout<<n<<" "<<cnt<<endl;
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}