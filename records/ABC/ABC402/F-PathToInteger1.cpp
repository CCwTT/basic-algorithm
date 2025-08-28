//https://atcoder.jp/contests/abc402/tasks/abc402_f
//scale breaking down
//time complexity:O(n)*O(2^n)*O(nlogn)=O(n^2logn2^n) 
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
	ll ans=0;
	auto helper=[&](ll x)->void{
		ll y=n+1-x;
		
		function<set<ll>(ll,ll)> dfs1=[&](ll ex,ll ey)->set<ll>{
			if(ex==1&&ey==1){
				return {grid[ex][ey]};
			}
			set<ll> st;
			if(ex-1>=1){
				auto st1=dfs1(ex-1,ey);
				for(auto e:st1){
					st.insert((e+grid[ex][ey])%mod);
				}
			}
			if(ey-1>=1){
				auto st2=dfs1(ex,ey-1);
				for(auto e:st2){
					st.insert((e+grid[ex][ey])%mod);
				}
			}
			return st;
		};
		
		function<set<ll>(ll,ll)> dfs2=[&](ll sx,ll sy)->set<ll>{
			if(sx==n&&sy==n){
				return {grid[sx][sy]};
			}
			set<ll> st;
			if(sx+1<=n){
				auto st1=dfs2(sx+1,sy);
				for(auto e:st1){
					st.insert((e+grid[sx][sy])%mod);
				}
			}
			if(sy+1<=n){
				auto st2=dfs2(sx,sy+1);
				for(auto e:st2){
					st.insert((e+grid[sx][sy])%mod);
				}
			}
			return st;
		};
		
		auto st1=dfs1(x,y);
		set<ll> st2;
		if(x+1<=n){
			auto st21=dfs2(x+1,y);
			for(auto e:st21){
				st2.insert(e);
			}
		}
		if(y+1<=n){
			auto st22=dfs2(x,y+1);
			for(auto e:st22){
				st2.insert(e);
			}
		}
		for(auto e:st1){
			ans=max({ans,(e+*st2.rbegin())%mod});
			auto it=st2.upper_bound(mod-1-e);
			if(it!=st2.begin()){
				ans=max(ans,e+*prev(it));
			}
		}
	};
	
	for(ll i=1;i<=n;i++){
		helper(i);
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
