#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//@@@
//https://acm.tju.edu.cn/group/1010/problem/2025TJUACM3-1021
//if bipartite return 1,else return 0
bool check_bipartite(vector<vector<ll>>& g){
	ll n=g.size();
	vector<ll> color(n,-1);
	function<bool(ll,ll)> dfs=[&](ll x,ll c)->bool{
		color[x]=c;
		for(auto& y:g[x]){
			if(!~color[y]&&!dfs(y,1-c)||color[y]==c){
				return false;
			}
		} 
		return true;
	};
	for(ll i=0;i<n;i++){
		if(!~color[i]&&!dfs(i,0)){
			return false;
		}
	}
	return true;
}


signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	return 0;
} 


