// https://www.luogu.com.cn/problem/P1196
// i dont really understand
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	ll n,X;
	cin>>n>>X;
	vector<ll> u(n+1),d(n+1);
	for(ll i=1;i<=n;i++){
		cin>>u[i]>>d[i];
	}
	ll sum=accumulate(u.begin(),u.end(),0ll)
		 + accumulate(d.begin(),d.end(),0ll);
	for(ll i=2;i<=n;i++){
		if(u[i]>u[i-1]+X){
			u[i]=u[i-1]+X;
		}
		if(d[i]>d[i-1]+X){
			d[i]=d[i-1]+X;
		}
	}
	for(ll i=n-1;i>=1;i--){
		if(u[i]>u[i+1]+X){
			u[i]=u[i+1]+X;
		}
		if(d[i]>d[i+1]+X){
			d[i]=d[i+1]+X;
		}
	}
	ll h=2e9;
	for(ll i=1;i<=n;i++){
		h=min(h,u[i]+d[i]);
	}
	cout<<sum-h*n<<endl;
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
