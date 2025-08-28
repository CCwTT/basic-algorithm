//https://www.lanqiao.cn/problems/20171/learning/
//@@@
//gcd,lcm,principle of multiplication,principle of inclusion-exclusion

//Given two numbers x and y, find the number of different sequences (a₁,a₂,…,aₙ) of length n such that 
//the gcd of all its elements is x and the lcm is y.

//KNOWLEDGE:
//gcd(ax,ay)=a*gcd(x,y) lcm(ax,ay)=a*lcm(x,y)
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n
typedef long long ll;
const ll mod=998244353;

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

void solve(){
    ll x,y,n;
    cin>>x>>y>>n;

    ll z=y/x;
    unordered_map<ll,ll> mp;

    for(ll i=2;i*i<=z;++i){
        while(z%i==0){
            mp[i]++;
            z/=i;
        }
    }
    if(z>1) mp[z]++;
    
    ll ans=1;
    for(auto [p,cnt]:mp){
        ll term=(qpow(cnt+1,n)-2*qpow(cnt,n)+qpow(cnt-1,n))%mod;
        term=(term+mod)%mod; 
        ans=ans*term%mod;
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}