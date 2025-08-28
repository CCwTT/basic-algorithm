//https://acm.hdu.edu.cn/contest/problem?cid=1174&pid=1012
//@@@
//Chebyshev distance and Manhattan distance
//link:records\2025NewCoder_Training4\核心共振.cpp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll mod=1e9+7;
const ll inv2=(mod+1)/2;

struct node{
    ll x,y,v;
    ll w;
};

ll compute(vector<node>& a){
    ll Sw=0,Sv=0,Swv=0;
    ll res=0;
    int i=0;
    for(auto& [x,y,v,w]:a){
        res=((res+w*Sv%mod-Swv+i*w%mod*v%mod-v*Sw%mod)%mod+mod)%mod;
        Sw=(Sw+w)%mod;
        Sv=(Sv+v)%mod;
        Swv=(Swv+w*v%mod)%mod;
        i++;
    }
    return res;
}

void solve(){
    ll n;
    cin>>n;
    vector<node> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i].x>>a[i].y>>a[i].v;
    }
    ll ans=0;
    for(ll i=0;i<n;i++){
        a[i].w=a[i].x+a[i].y;
    }
    sort(a.begin(),a.end(),[&](const auto& u,const auto& v){
        return u.w<v.w;
    });
    ans+=compute(a);
    ans%=mod;

    for(ll i=0;i<n;i++){
        a[i].w=a[i].x-a[i].y;
    }
    sort(a.begin(),a.end(),[&](const auto& u,const auto& v){
        return u.w<v.w;
    });
    ans+=compute(a);
    ans%=mod;
    cout<<ans*inv2%mod<<endl; 
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