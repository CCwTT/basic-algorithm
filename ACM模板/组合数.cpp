#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//�����(����)
//long long C(ll n,ll m){
//	m=min(m,n-m);
//	long long res=1;
//	for(ll i=1;i<=m;i++){
//		res=res*(n+1-i)/i;
//	}
//	return res;
//} 


//��ʽ�� (��) 
const ll MOD=1e9+7;

//x>=0
ll qpow(ll x,ll n){
	if(x==0) return 0;
	ll res=1;
	while(n){
		if(n&1) res=res*x%MOD;
		n>>=1;
		x=x*x%MOD;
	}
	return res;
} 

const ll MX=2e6+5;
ll fac[MX],inv_fac[MX];
int init=[]{
	fac[0]=1;
	for(ll i=1;i<MX;i++){
		fac[i]=fac[i-1]*i%MOD;
	}
	inv_fac[MX-1]=qpow(fac[MX-1],MOD-2);
	for(ll i=MX-2;i>=0;i--){
		inv_fac[i]=inv_fac[i+1]*(i+1)%MOD;
	}
	return 0;
}();

ll C(ll n,ll m){
	if(n<=0||n<m) return 0;
	return fac[n]*inv_fac[m]%MOD*inv_fac[n-m]%MOD;
}

//¬��˹���� (��)
const ll p=19937;
ll lucas(ll n,ll m){
	if(n<=0||n<m) return 0;
	if(m==0) return 1;
	return lucas(n/p,m/p)%p*C(n%p,m%p)%p;
}

//��̬�滮�����(O(n^2))
//ll c[31][31];
//auto init=[]{
//	for(ll i=0;i<31;i++){
//		c[i][0]=1;
//		for(ll j=1;j<=i;j++){
//			c[i][j]=c[i-1][j-1]+c[i-1][j];
//		}
//	}
//	return 0;
//}();

//��������д��
//const ll MX=1000;
//ll inv[MX+1],fac[MX+1],inv_fac[MX+1];
//ll init=[]{
//	inv[0]=fac[0]=inv_fac[0]=1;
//	inv[1]=fac[1]=inv_fac[1]=1;
//	for(ll i=2;i<=MX;i++){
//		inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
//		fac[i]=1LL*fac[i-1]%MOD;
//		inv_fac[i]=1LL*inv_fac[i-1]*inv[i]%MOD;
//	}
//	return 0;
//}();
//

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for(ll i=0;i<10;i++){
		cout<<(1-i&1*2)<<endl;
	}
	return 0;
} 
