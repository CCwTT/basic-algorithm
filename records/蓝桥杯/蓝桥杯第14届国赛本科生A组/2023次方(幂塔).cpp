//https://www.lanqiao.cn/problems/17095/learning/
//@@@
//Euler's power reduction,power tower
//KNOWLEGE:phi(x)<=x/2
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
			while(x%i==0) x/=i;
		}
	}
	if(x>1) res=res/x*(x-1);
	return res;
}

ll qpow(ll x,ll n,ll p){
	x%=p;
	ll phi=__phi(p);
	if(n>phi) n=n%phi+phi;

	if(x==0) return 0;	
	ll res=1;
	while(n){
		if(n&1) res=res*x%p;
		n>>=1;
		x=x*x%p;
	}
	return res;
} 

void solve(){
	function<ll(ll,ll)> dfs=[&](ll x,ll p)->ll{
		if(p==1) return 0;
		//exponent big enough
		ll exp=dfs(x+1,__phi(p))+__phi(p);
		return qpow(x,exp,p);
	};
	cout<<dfs(2,2023)<<endl;
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
