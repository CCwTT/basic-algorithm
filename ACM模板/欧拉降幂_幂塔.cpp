//https://www.lanqiao.cn/problems/17095/learning/
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}


ll __phi(ll x){
    ll res=x;
    for(ll i=2;i*i<=x;i++){
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0){
                x/=i;
            }
        }
    }
    if(x>1){
        res=res/x*(x-1);
    }
    return res;
}

pair<ll,bool> qpow(ll x,ll n,ll md){
    x%=md;
    ll phimd=__phi(md);
    if(n>phimd) n=n%phimd+phimd;

    if(x==0) return {0,false};
    ll res=1;
    bool exceed=false;
    while(n){
        if(n&1){
            res=res*x;
            if(res>=md){
                exceed=true;
                res%=md;
            }
        }
        n>>=1;
        x=x*x;
        if(x>=md&&n){
            exceed=true;
            x%=md;
        }
    }
    return {res,exceed};
}

//O(log(md)·√md)
pair<ll,bool> power_tower(vector<ll>& a,ll p,ll md){
    if(md==1) return {0,false};
    ll n=a.size();
    if(p==n-1) return {a[p]%md,false};
    if(p==n-2) return qpow(a[p],a[p+1],md);
    auto [e,exceed]=power_tower(a,p+1,__phi(md));
    if(exceed){
        e+=__phi(md);
    }
    return qpow(a[p],e,md);
}

void solve(){
    vector<ll> a;
    for(ll i=2;i<=2023;i++){
        a.push_back(i);
    }
    cout<<power_tower(a,0,2023).first<<endl;
    // a={2,2,2};
    // cout<<power_tower(a,0,1000000).first<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
