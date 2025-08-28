//https://www.lanqiao.cn/problems/2090/learning/?isWithAnswer=true
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline bool squareNumber(ll x){
	ll y=sqrt(x);
	while(y*y<=x){
		if(y*y==x) return true;
		y++;
	}
	return false;
}

inline bool cubicNumber(ll x){
	ll y=pow(x,1.0/3);
	while(y*y*y<=x){
		if(y*y*y==x) return true;
		y++;
	}
	return false;
}

//pow(1e18,1.0/5)=3981.07
const ll MX=4010;
vector<ll> primes;
ll np[MX];
int init=[]{
	for(ll i=2;i<MX;i++){
		if(!np[i]) primes.push_back(i);
		for(auto p:primes){
			if(p*i>=MX) break;
			np[p*i]=true;
			if(i%p==0) break;
		}
	}
	return 0;
}();

void solve(){
	ll X;
	cin>>X;
	if(squareNumber(X)||cubicNumber(X)){
		cout<<"yes"<<endl;
		return;
	}
	bool flag=true;
	for(auto p:primes){
		ll q=0;
		if(X%p==0){
			while(X%p==0){
				q++;
				X/=p;
			}
		}
		if(q==1){
			flag=false;
			break;
		}
	}
	if(flag&&(squareNumber(X)||cubicNumber(X))){
		cout<<"yes"<<endl;
	}else{
		cout<<"no"<<endl;
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	cin>>T;
	while(T--){
		solve();
	}	
	return 0;
} 
