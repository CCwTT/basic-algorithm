// https://www.luogu.com.cn/problem/P1196
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class WDsu{
public:
	vector<ll> f;
	vector<ll> dist;
	vector<ll> tot;

	WDsu(ll n):f(n),dist(n),tot(n,1){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		ll _fx=f[x];
		return f[x]==x?x:(f[x]=find(f[x]),dist[x]+=dist[_fx],f[x]);
	}

	//y is the referenced system
	void join(ll x,ll y,ll v){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		f[fy]=fx;
		dist[fy]=v+dist[x]-dist[y];
		tot[fx]+=tot[fy];
	}

	bool check(ll x,ll y){
		return find(x)==find(y);
	}

	ll query(ll x,ll y){
		return check(x,y)?dist[y]-dist[x]:LLONG_MAX;
	}
};

void solve(){
	ll n;
	cin>>n; 
	WDsu dsu(n+2);
	char op;
	while(cin>>op){
		if(op=='M'){
			ll x,y;
			cin>>x>>y;
			ll fx=dsu.find(x);
			ll fy=dsu.find(y);
			dsu.join(fy,fx,dsu.tot[fy]);
		}else{
			ll x,y;
			cin>>x>>y;
			ll ret=dsu.query(x,y);
			cout<<(ret==LLONG_MAX?-1:llabs(ret)-1)<<endl;
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
