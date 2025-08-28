//https://codeforces.com/contest/2090/problem/E1
//@@@
//Monotonic stack
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
	ll n,k;
	cin>>n>>k;
	vector<ll> a(n*2+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}	
	for(ll i=1;i<=n;i++){
		ll bi;
		cin>>bi;
		a[i]=a[i+n]=a[i]-bi;
	}
	vector<ll> s(2*n+2);
	partial_sum(a.begin()+1,a.end(),s.begin()+1);
	//find the smallest j>=i s.t. s[j]<=s[i-1];
	stack<ll> stk;
	vector<ll> rnear(2*n+1,2*n+5);
	for(ll i=2*n;i>=1;i--){
		while(!stk.empty()&&s[stk.top()]>s[i-1]){
			stk.pop();
		}
		if(!stk.empty()) rnear[i]=stk.top();
		stk.push(i);
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(s[i]<=s[i-1]) rnear[i]=i;
		ans=max(ans,rnear[i]-i+1);
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
