//https://atcoder.jp/contests/abc400/tasks/abc400_e
//Eratosthenes' sieve,binary search
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> tab;
const ll MX=1e6+5;
vector<ll> primes;
ll cntp[MX];
int init=[]{
	for(ll i=2;i<MX;i++){
		if(!cntp[i]){
			primes.push_back(i);
			for(ll j=i;j<MX;j+=i){
				cntp[j]++;
			}
		}
	}

	for(ll i=6;i*i<=1e12;i++){
		if(cntp[i]==2) tab.push_back(i*i); 
	}
	return 0;
}();

void solve(){
	ll n;
	cin>>n;
	
	cout<<*prev(upper_bound(tab.begin(),tab.end(),n))<<endl;
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
