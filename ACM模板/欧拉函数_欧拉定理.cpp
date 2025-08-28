#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://atcoder.jp/contests/abc228/tasks/abc228_e
//https://www.lanqiao.cn/problems/17095/learning/
//@@@
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
	ll phip=__phi(p);
	if(n>phip) n=n%phip+phip;

	if(x==0) return 0;	
	ll res=1;
	while(n){
		if(n&1) res=res*x%p;
		n>>=1;
		x=x*x%p;
	}
	return res;
} 


//ŷ��ɸ������ŷ������O(n)
const int MX=1e6;
vector<int> primes;
bool np[MX+1];
ll phi[MX+1];

void get_phi(){
	phi[1]=1;
	for(int i=2;i<=MX;i++){
		if(!np[i]){
			primes.push_back(i);
			phi[i]=i-1;
		}
		for(auto& p:primes){
			if(p*i>MX) break;
			np[p*i]=true;
			if(i%p==0){
				phi[p*i]=p*phi[i];
				break;
			}
			phi[p*i]=phi[p]*phi[i];
		}
	}
} 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    return 0;
}
