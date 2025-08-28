//https://atcoder.jp/contests/abc406/tasks/abc406_f
//@@@
//dfn,BIT 
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class BIT{
public:
	ll n;
	vector<ll> c;
	BIT(ll sz):n(sz-1),c(sz) {};
	
	void update(ll i,ll v){
		while(i<=n){
			c[i]+=v;
			i+=i&-i;
		}
	}

	ll query(ll i){
		ll res=0;
		while(i>0){
			res+=c[i];
			i&=i-1;
		}
		return res;
	}

	ll query(ll l,ll r){
		return query(r)-query(l-1);
	}
};

void solve(){
	ll n;
	cin>>n;
	vector<vector<ll>> g(n+1);
	vector<pair<ll,ll>> edges(n);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		edges[i]={u,v};
	}
	BIT fenwick(n+1);
	for(ll i=1;i<=n;i++){
		fenwick.update(i,1);
	}
	vector<ll> l(n+1),r(n+1);
	ll acc=0;
	function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
		l[x]=++acc;
		for(auto y:g[x]) if(y!=fa){
			dfs(y,x);
			r[y]=acc;
		}
	};
	dfs(1,0);
	r[1]=acc;
	ll Q;
	cin>>Q;
	while(Q--){
		ll op;
		cin>>op;
		if(op==1){
			ll x,w;
			cin>>x>>w;
			fenwick.update(l[x],w);
		}else{
			ll y;
			cin>>y;
			auto [u,v]=edges[y];
			ll x=u;
			if(l[v]>l[u]) x=v;
			cout<<llabs(fenwick.query(n)-2ll*fenwick.query(l[x],r[x]))<<endl;
		}
	}
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
