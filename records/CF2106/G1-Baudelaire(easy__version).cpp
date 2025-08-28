//https://codeforces.com/problemset/problem/2106/F
//@@@
//interactive,binary search
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
	vector<ll> a(n+1);
	for(ll i=0;i<n-1;i++){
		ll u,v;
		cin>>u>>v;
	}
	ll Q=0;
	auto ask=[&](ll op,const vector<ll>& v)->ll{
		if(++Q>n+200){
			assert(false);
		}	
		cout<<"? "<<op<<" ";
		if(op==1){
			cout<<v.size()<<" ";
			for(auto e:v) cout<<e<<" ";
			cout<<endl;
			ll res=0;
			cin>>res;
			return res;
		}else{
			cout<<v[0]<<endl;
			return 0;
		}
	};
	ll rt=0;
	vector<ll> vec;
	for(ll i=2;i<=n;i++) vec.push_back(i);
	ll bef=ask(1,vec);
	ask(2,vector<ll>{1});
	ll af=ask(1,vec);
	if(llabs(bef-af)==2*vec.size()){
		rt=1;
	}else{
		ll l=0,r=vec.size()-1;
		while(l<=r){
			ll m=l+r>>1;
			vector<ll> query(vec.begin()+l,vec.begin()+m+1);
			ll bef=ask(1,query);
			ask(2,vector<ll>{1});
			ll af=ask(1,query);
			//rt is in the query section
			if(llabs(bef-af)!=2*(m-l+1)){
				r=m-1;
				rt=vec[m];
			}else{ //rt is not in the query section
				l=m+1;
			}
		}
	}
	for(ll i=1;i<=n;i++){
		a[i]=ask(1,vector<ll>{i});
	}
	if(rt==1){
		for(ll i=2;i<=n;i++) a[i]-=a[1];
	}else{
		for(ll i=2;i<=n;i++) if(i!=rt) a[i]-=a[1];
		a[1]-=a[rt];
	}
	cout<<"! ";
	for(ll i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
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
