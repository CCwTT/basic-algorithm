//https://atcoder.jp/contests/abc402/tasks/abc402_f
//scale breaking down
//time complexity:O(n*2^n)+O(n*nlog(n))=O(n*2^n)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod;

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

void solve(){
	ll n;
	cin>>n>>mod;
	vector<vector<ll>> grid(n+1,vector<ll>(n+1));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			cin>>grid[i][j];
			grid[i][j]=qpow(10,2*n-i-j)*grid[i][j]%mod;
		}
	}
	if(n==1){
		cout<<grid[1][1]<<endl;
		return;
	}
	vector<set<ll>> st1(n+1),st2(n+1);
	for(ll mask=0;mask<(1<<(n-1));mask++){
		ll x=1,y=1,sum=grid[1][1];
		for(ll i=0;i<n-1;i++){
			if(mask>>i&1){
				x++;
			}else{
				y++;
			}
			sum=(sum+grid[x][y])%mod;
		}
		st1[x].insert(sum);
	}
	for(ll mask=0;mask<(1<<(n-1));mask++){
		ll x=n,y=n,sum=grid[n][n];
		for(ll i=0;i<n-1;i++){
			if(mask>>i&1){
				x--;
			}else{
				y--;
			}
			if(i<n-2) sum=(sum+grid[x][y])%mod;
		}
		st2[x].insert(sum);
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		for(auto e:st1[i]){
			ans=max({ans,(e+*st2[i].rbegin())%mod});
			auto it=st2[i].upper_bound(mod-1-e);
			if(it!=st2[i].begin()){
				ans=max(ans,e+*prev(it));
			}
		}
	}
	cout<<ans<<endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	while(T--){
		solve();
	}
	return 0;
} 
