//https://atcoder.jp/contests/abc401/tasks/abc401_e
//dsu,STL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Dsu{
public:
	vector<ll> f;
	vector<ll> tot;
	Dsu(ll n):f(n),tot(n,1){
		iota(f.begin(),f.end(),0);
	}
	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	bool check(ll x,ll y){
		return find(x)==find(y);
	}
	void join(ll x,ll y){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		tot[fx]+=tot[fy];
		f[fy]=fx;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> g(n+1);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	} 
	Dsu dsu(n+1);
	unordered_set<ll> toBeErased;
	for(ll x=1;x<=n;x++){
		if(toBeErased.count(x)){
			toBeErased.erase(x);
		}
		for(auto y:g[x]){
			if(y>x){
				toBeErased.insert(y);
			}else{
				dsu.join(x,y);
			}
		}
		if(dsu.tot[dsu.find(x)]==x){
			cout<<toBeErased.size()<<endl;
		}else{
			cout<<-1<<endl;
		}
	}
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
