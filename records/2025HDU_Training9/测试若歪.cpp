//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1012
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=1e5+10;
ll n,m;
ll p[N];

void solve(){
    cin>>n>>m;
    unordered_map<ll,ll> mp;
    vector<ll> a;
    for(ll i=1;i<=m;i++){
        cin>>p[i];
        if(!mp[p[i]]) a.push_back(p[i]);
        mp[p[i]]++;
    }
    vector<pll> b;
    for(auto [x,y]:mp){
        b.emplace_back(y,x);
    }
    sort(b.begin(),b.end(),[&](pll& u,pll& v){
        return u.first^v.first?u.first>v.first:u.second<v.second;
    });
    ll ans=0;
    for(ll i=0;i<b.size();i++){
        if(b[i].second!=a[i]) ans++;
    }
    cout<<ans<<endl;
}

void clear(){

}

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