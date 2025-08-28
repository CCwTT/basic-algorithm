//https://codeforces.com/problemset/problem/2106/F
//@@@
//Dsu method optimization
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void solve(){
	ll n;
	cin>>n;
	string s;
	cin>>s;
	s=" "+s;
	vector<ll> top(n+1,0),bot(n+1,0);
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(s[i]=='1'){
			top[i]=bot[i-1]+1;
		}else{
			top[i]=top[i-1]+(i-1);
			bot[i]=bot[i-1]+(n-i);
		}
		ans=max(ans,max(top[i],bot[i]));
	}
	cout<<ans<<endl;
	
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
