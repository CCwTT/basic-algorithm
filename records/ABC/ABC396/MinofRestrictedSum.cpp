//https://atcoder.jp/contests/abc396/tasks/abc396_e
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<pair<ll,ll>>> g(n+1);
	for(ll i=0;i<m;i++){
		ll x,y,w;
		cin>>x>>y>>w;
		g[x].emplace_back(w,y);
		g[y].emplace_back(w,x);
	}
	vector<ll> vis(n+1,false);

	vector<ll> comp;
	vector<ll> val(n+1,-1);
	function<void(ll)> dfs=[&](ll x)->void{
		vis[x]=true;
		comp.push_back(x);
		for(auto& [w,y]:g[x]){
			if(vis[y]){
				if(val[y]!=(val[x]^w)){
					cout<<-1<<endl;
					exit(0);
				}
				continue;
			}
			val[y]=val[x]^w;
			dfs(y);
		}
	};

	vector<ll> ans(n+1,0);
	for(ll i=1;i<=n;i++){
		if(vis[i]) continue;
		comp.clear();
		val[i]=0;
		dfs(i);
		for(ll j=0;j<30;j++){
			ll cnt=0;
			for(auto k:comp){
				if(val[k]>>j&1){
					cnt++;
				}
			}
			if(cnt<comp.size()-cnt){
				for(auto k:comp){
					if(val[k]>>j&1){
						ans[k]|=1ll<<j;
					}
				}
			}else{
				for(auto k:comp){
					if(!(val[k]>>j&1)){
						ans[k]|=1ll<<j;
					}
				}
			}
		}
	}
	for(ll i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
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
