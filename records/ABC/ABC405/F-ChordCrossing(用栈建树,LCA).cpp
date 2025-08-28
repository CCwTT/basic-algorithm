//https://atcoder.jp/contests/abc405/tasks/abc405_f
//@@@
//graph,lca,stack
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class Info{
public:
	vector<ll> dep;
	vector<vector<ll>> stj;

	Info(vector<vector<ll>>& g){
		ll n=g.size();
		ll high=__lg(n);
		dep.resize(n);
		stj.resize(n,vector<ll>(high+1,-1));
		function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
			stj[x][0]=fa;
			for(ll j=1;j<=high;j++){
				if(~stj[x][j-1]){
					stj[x][j]=stj[stj[x][j-1]][j-1];
				}
			}
			for(auto y:g[x]) if(y!=fa){
				dep[y]=dep[x]+1;
				dfs(y,x);
			}
		}; 
		dfs(0,-1);
	}
	
	ll getKthAncestjor(ll x,ll k){
		for(;k&&~x;k&=k-1){
			x=stj[x][__builtin_ctzll(k)];
		}
		return x;
	}
	
	ll __lca(ll x,ll y){
		if(dep[y]>dep[x]) swap(x,y);
		x=getKthAncestjor(x,dep[x]-dep[y]);
		if(x==y){
			return x;
		}
		for(ll i=stj[x].size()-1;i>=0;i--){
			if(stj[x][i]!=stj[y][i]){
				x=stj[x][i];
				y=stj[y][i];
			}
		}
		return stj[x][0];
	} 
};
void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> id(2*n+1);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		id[u]=id[v]=i;
	}
	vector<ll> min_cov(2*n+1);
	vector<vector<ll>> g(m+1);
	stack<ll> stk;
	stk.push(0);
	for(ll i=1;i<=2*n;i++){
		if(~i&1){
			if(!id[i]) continue;
			if(stk.top()==id[i]){
				stk.pop();
				g[stk.top()].push_back(id[i]);
				g[id[i]].push_back(stk.top());
			}else{
				stk.push(id[i]);
			}
		}else{
			min_cov[i]=stk.top();
		}
	}
	Info info(g);
	ll Q;
	cin>>Q;
	while(Q--){
		ll x,y;
		cin>>x>>y;
		ll u=min_cov[x];
		ll v=min_cov[y];
		ll lca=info.__lca(u,v);
		cout<<info.dep[u]+info.dep[v]-2*info.dep[lca]<<endl;
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
