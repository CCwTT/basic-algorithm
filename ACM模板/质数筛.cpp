#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Log(ll a[],ll n){
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

//sieve of Eratosthenes
//@@@
// const ll MX=2e6+5;
// vector<ll> primes;
// bool np[MX];
// int init=[]{
// 	np[0]=np[1]=true;
// 	for(ll i=2;i<MX;i++){
// 		if(!np[i]){
// 			primes.push_back(i);
// 			for(ll j=i*i;j<MX;j+=i){
// 				np[j]=true;
// 			}
// 		}
// 	}
// 	return 0;
// }();

//sieve of Euler/linear sieve
//@@@
const ll MX=2e6+5;
vector<ll> primes;
bool np[MX];
int init=[]{
	np[0]=np[1]=true;
	for(ll i=2;i<MX;i++){
		if(!np[i]) primes.push_back(i);
		for(auto& p:primes){
			if(p*i>=MX) break;
			np[p*i]=true;
			if(i%p==0) break;
		}
	}
	return 0;
}();


//sieve of Eratosthenes to get least prime factors
// const ll MX=2e6+5;
// ll lpf[MX];
// ll init=[]{
// 	for(ll i=2;i<MX;i++){
// 		if(!lpf[i]){ 
// 			for(ll j=i;j<MX;j+=i){
// 				if(!lpf[j]){
// 					lpf[j]=i;
// 				} 
// 			}
// 		}
// 	}
// 	return 0;
// }(); 

//sieve of Euler to get least prime factors
const ll MX=2e6+5;
vector<ll> primes;
ll lpf[MX];
ll init=[]{
	for(ll i=2;i<MX;i++) lpf[i]=i;
	for(ll i=2;i<MX;i++){
		if(lpf[i]==i) primes.push_back(i);
		for(auto& p:primes){
			if(p*i>=MX) break;
			lpf[p*i]=p;
			if(i%p==0) break;
		}
	}
	return 0;
}();

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
 	Log(primes);
    return 0;
}
