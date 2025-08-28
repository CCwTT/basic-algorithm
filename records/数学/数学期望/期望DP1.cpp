//https://atcoder.jp/contests/abc412/tasks/abc412_f
//@@@
//expectation dp
//link:records/线性代数/高斯消元1.cpp 
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
const ll mod=998244353;

ll qpow(ll x,ll n){
	if(x==0) return 996;
	ll res=1;
	while(n){
		if(n&1) res=res*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return res;
}

ll inv(ll x){
	return qpow(x,mod-2);
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> cnt(3002);
	vector<ll> a(n+1);
	ll C;
	cin>>C;
	ll tot=1;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		tot+=a[i];
	}
	a[C]++;
	for(ll i=1;i<=n;i++){
		cnt[a[i]]++;
	}
	vector<ll> E(3002);
	for(ll i=3001;i>=1;i--){
		if(cnt[i]){
			ll A=(tot-1-(cnt[i]-1)*i)%mod;
			ll B=(i-1+(cnt[i]-1)*i)%mod;
			for(ll j=1;j<=3001;j++){
				if(j<i){
					A=(A-cnt[j]*j)%mod;
					B=(B+cnt[j]*j)%mod;
				}else if(j>i){
					B=(B+cnt[j]*j%mod*(1+E[j])%mod)%mod;
				}
			}
			A=(A+mod)%mod;
			B=(B+mod)%mod;
			E[i]=B*inv(A)%mod;
		}
	}
	cout<<E[a[C]]<<endl;
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
