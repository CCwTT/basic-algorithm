//https://atcoder.jp/contests/agc028/tasks/agc028_b
//@@@
//expectation,contribution,Cartesian tree
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

const ll mod=1e9+7;
const ll MX=1e5+5;
ll inv[MX];
ll sum[MX];

ll init=[]{
	inv[1]=1;
    for(ll i=2;i<MX;i++){
        inv[i]=mod-inv[mod%i]*(mod/i)%mod;
    }
    for(ll i=1;i<MX;i++){
        sum[i]=(sum[i-1]+inv[i])%mod;
    }
	return 0;
}();

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans=(ans+(sum[i]+sum[n+1-i]-1)*a[i])%mod;
	}
	for(ll i=1;i<=n;i++){
		ans=ans*i%mod;
	}
	cout<<ans<<endl;
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

