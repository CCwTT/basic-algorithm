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

vector<ll> find_centroid(vector<vector<pair<ll,ll>>>& g,vector<ll>& a){
	ll n=g.size()-1;
	vector<ll> sz(n+1);
	function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
		sz[x]=a[x];
		for(auto& [w,y]:g[x]) if(y!=fa){
			dfs1(y,x);
			sz[x]+=sz[y];
		}
	};
	dfs1(1,0);

	ll A=accumulate(a.begin()+1,a.end(),0ll);
	vector<ll> mxsub(n+1);
	function<void(ll,ll)> dfs2=[&](ll x,ll fa)->void{
        mxsub[x]=A-sz[x];
        for (auto& [w,y]:g[x]) if(y!=fa){
          	dfs2(y,x);
            mxsub[x]=max(mxsub[x],sz[y]);    
        }
	}; 
	dfs2(1,0);
	
	vector<ll> res;
	for(ll i=1;i<=n;i++){
		if(mxsub[i]<=A/2){
			res.push_back(i);
		}
	}
	return res;
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	} 
	vector<vector<pair<ll,ll>>> g(n+1);
	for(ll i=1;i<=n-1;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		g[u].emplace_back(w,v);
		g[v].emplace_back(w,u);
	}
	
	ll centroid=find_centroid(g,a)[0];
	
	ll ans=0;
	function<void(ll,ll,ll)> dfs=[&](ll x,ll fa,ll above)->void{
		ans+=a[x]*above;
		for(auto& [w,y]:g[x]) if(y!=fa){
			dfs(y,x,above+w);
		}
	};
	dfs(centroid,0,0);
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

