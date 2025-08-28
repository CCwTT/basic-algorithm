const int mod=1e9+7; 
typedef long long ll;

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

ll inv(ll x){
	return qpow(x,mod-2);
}

//���Ե�������Ԫ (Ҫ��mod��������)
const int MX=mod-1;
int inv[MX+1];
int init=[]{
	inv[1]=1;
	for(int i=2;i<=MX;i++){
		inv[i]=mod-1ll*inv[mod%i]*(mod/i)%mod;
	}
	return 0;
}();
