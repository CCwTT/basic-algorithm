//https://codeforces.com/problemset/problem/1406/C
//@@@
//rootless tree,centroid,construcive
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

vector<ll> find_centroid(vector<vector<ll>>& g){  //vector<vector<pair<ll,ll>>>& g
	ll n=g.size()-1;
	vector<ll> sz(n+1);
	function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
		sz[x]=1;
		for(auto& y:g[x]) if(y!=fa){   //auto& [w,y]
			dfs1(y,x);
			sz[x]+=sz[y];
		}
	};
	dfs1(1,0);

	vector<ll> mxsub(n+1);
	function<void(ll,ll)> dfs2=[&](ll x,ll fa)->void{
        mxsub[x]=n-sz[x];
        for (ll y:g[x]) if(y!=fa){    //auto& [w,y]
          	dfs2(y,x);
            mxsub[x]=max(mxsub[x],sz[y]);    
        }
	}; 
	dfs2(1,0);

	vector<ll> res;
	for(ll i=1;i<=n;i++){
		if(mxsub[i]<=n/2){
			res.push_back(i);
		}
	}

	return res;
}

void solve(){
	ll n;
	cin>>n;
	vector<vector<ll>> g(n+1);
	ll u,v;
	for(ll i=1;i<=n-1;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	auto centroid=find_centroid(g);
	if(centroid.size()==1){
		cout<<u<<" "<<v<<endl;
		cout<<u<<" "<<v<<endl;
		return;
	}
	
	ll leaf,leafFa;
	function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
		for(auto& y:g[x]) if(y!=fa){
			dfs(y,x);
			return;
		}
		leaf=x,leafFa=fa;
	};
	dfs(centroid[1],centroid[0]);
	
	cout<<leaf<<" "<<leafFa<<endl;
	cout<<leaf<<" "<<centroid[0]<<endl;
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
