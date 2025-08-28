//https://atcoder.jp/contests/abc406/tasks/abc406_e
//@@@
//digit dp,pre-processing
//KNOWLEDGE:When it is needed to maintain some sort of sum in digit dp dfs,the traditional digit dp model seems unworkable.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;

ll qpow(ll x,ll n){
   if(x==0) return 0;
   ll res=1;
   while(n){
      if(n&1) res=res*x%mod;
      n>>=1;
      x=x*x%mod;
   }
   return res;
}

#define MX 65
ll c[MX][MX]; //c[i][j]=(the number of x  s.t. 0<=x<(2^i), popcount(x)=j) for 0<=j<=i<=60
ll s[MX][MX]; //s[i][j]=(the sum    of x  s.t. 0<=x<(2^i), popcount(x)=j) for 0<=j<=i<=60
int init=[]{
	c[0][0]=1;
	for(ll i=1;i<MX;i++){
        c[i][0]=1;
		for(ll j=1;j<=i;j++){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
			s[i][j]=(s[i-1][j]+s[i-1][j-1]+qpow(2,i-1)*c[i-1][j-1]%mod)%mod;
		}
	}
   return 0;
}();

void solve(){
   ll n,K;
   cin>>n>>K;
   ll high=__lg(n);
	ll acc=0;
	ll above=0;
	ll ans=0;
	for(ll d=high;d>=0;d--) if(n&1ll<<d){
		if(acc<=K){
			ans=(ans+s[d][K-acc])%mod;
			ans=(ans+above*c[d][K-acc]%mod)%mod;
		}
		acc++;
		above=(above+qpow(2,d))%mod;
	}
	if(acc==K) ans=(ans+above)%mod;
	cout<<ans<<endl;
}

signed main(){
   ll T=1;
   cin>>T;
   while(T--){
      solve();
   }
	return 0;
}
