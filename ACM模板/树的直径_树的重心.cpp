#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//����DP�� 
//@@@
//https://atcoder.jp/contests/abc401/tasks/abc401_f
ll diameter(vector<vector<ll>> &g){
	ll n=g.size();
	//if 1-indexed,it ought to be n=g.size()-1;
	ll ans=0;
	function<ll(ll,ll)> dfs=[&](ll x,ll fa)->ll{
		ll maxLen=0;
		for(ll y:g[x]) if(y!=fa) {
			ll len=dfs(y,fa)+1;
			ans=max(ans,maxLen+len);
			maxLen=max(maxLen,len);
		}
		return maxLen;
	};
	dfs(0,-1);
	return ans;
} 

//https://codeforces.com/contest/2106/problem/G2
//@@@
//1-indexed
//non-point-weighted+non-edge-weighted/edge-weighted
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



//https://www.luogu.com.cn/problem/P2986
//@@@
//1-indexed
//point-weighted+non-edge-weighted/edge-weighted
vector<ll> find_centroid(vector<vector<ll>>& g,vector<ll>& a){ //vector<vector<pair<ll,ll>>>& g
	ll n=g.size()-1;
	vector<ll> sz(n+1);
	function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
		sz[x]=a[x];
		for(auto& y:g[x]) if(y!=fa){  //auto& [w,y]
			dfs1(y,x);
			sz[x]+=sz[y];
		}
	};
	dfs1(1,0);

	ll A=accumulate(a.begin()+1,a.end(),0ll);
	vector<ll> mxsub(n+1);
	function<void(ll,ll)> dfs2=[&](ll x,ll fa)->void{
        mxsub[x]=A-sz[x];
        for(auto& y:g[x]) if(y!=fa){  //auto& [w,y]
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

//https://codeforces.com/contest/2106/problem/G2
//@@@
pair<ll,vector<vector<ll>>> build_centroid_tree(vector<vector<ll>>& g){
	ll n=g.size()-1;
	vector<vector<ll>> nextcd(n+1);
	vector<ll> mxsub(n+1);
	vector<bool> vis(n+1);
	vector<ll> sz(n+1);
	auto get_sz=[&](ll s)->void{
		function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
			sz[x]=1;
			for(auto& y:g[x]) if(y!=fa&&!vis[y]){   //auto& [w,y]
				dfs1(y,x);
				sz[x]+=sz[y];
			}
		};
		dfs1(s,0);
	};
	auto find_centroid=[&](ll s)->vector<ll>{ 
		get_sz(s);
		ll SZ=sz[s];
	
		vector<ll> res; //
		function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
			mxsub[x]=SZ-sz[x];
			for (ll y:g[x]) if(y!=fa&&!vis[y]){    //auto& [w,y]
				  dfs(y,x);
				mxsub[x]=max(mxsub[x],sz[y]);    
			}
			if(mxsub[x]<=SZ/2){ //
				res.push_back(x); //
			} //
		};
		dfs(s,0);
	
		return res;
	};
	auto build=[&](ll s)->vector<vector<ll>>{
		function<void(ll,ll)> dfs=[&](ll x,ll prev)->void{
			nextcd[prev].push_back(x);
			vis[x]=true;
			for(auto y:g[x]) if(!vis[y]){
				ll centroid=find_centroid(y)[0];
				dfs(centroid,x);
			}
		};
		dfs(s,0);
		return nextcd;
	};
	ll CD=find_centroid(1)[0];
	return {CD,build(CD)};
}

//@@@
//to get the length of longest tentacle of each of the nodes in g with time complexity
//in need of polishing!!! 
//https://atcoder.jp/contests/abc401/tasks/abc401_f
vector<ll> reach(vector<vector<ll>>& g){
	ll n=g.size();
	vector<ll> res(n,0);
	vector<ll> mx(n,0),mxid(n,-1),sem(n,0),semid(n,-1),my(n,1);
	function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
		for(auto y:g[x]) if(y!=fa){
			dfs(y,x);
			my[x]=max(my[x],my[y]+1);
			if(my[y]>mx[x]){
				sem[x]=mx[x];
				semid[x]=mxid[x];
				mx[x]=my[y];
				mxid[x]=y;
			}else if(my[y]>sem[x]){
				sem[x]=my[y];
				semid[x]=y;
			}
		}
	};
	dfs(0,-1);
	vector<ll> up(n,0);
	function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
		if(x==0){
			up[x]=0;
			res[x]=my[x];
		}else{
			if(x!=mxid[fa]){
				up[x]=max(up[fa]+1,my[fa]);
			}else{
				up[x]=max(up[fa]+1,1+sem[fa]);
			}
			res[x]=max(my[x],1+up[x]);
		}
		for(auto y:g[x]) if(y!=fa){
			dfs1(y,x);
		}
	};
	dfs1(0,-1);
	return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	
    return 0;
}

//KNOWLEDGE
/*
Definitions
1.The centroid of a tree is a node for which the size of its largest subtree is the smallest compared to the largest subtrees of all other nodes in the tree.
2.The centroid of a tree is a node such that the size of each of its subtrees does not exceed half (rounded down) of the total size of the tree.
3.The centroid of a tree is a node for which the sum of the lengths of the paths between it and all other nodes in the tree is minimized.
Other Properties
4.A tree has at most two centroids. In the case where there are two centroids, they are adjacent to each other.
5.When a leaf node is added to or removed from a tree, the centroid moves across at most one edge.
6.When two trees are joined together, the new centroid lies on the path connecting the centroids of the two original trees.
7.Whether we assign edge weights to a tree that originally had no edge weights, or we remove the edge weights from an edge-weighted tree, the centroid(s) of the tree remains unchanged.
*/


//tutorial
//https://codeforces.com/contest/2106/problem/G2
//@@@
//1-indexed
//non-point-weighted+non-edge-weighted/edge-weighted
vector<ll> find_centroid(vector<vector<ll>>& g){
	ll n=g.size()-1;
	vector<ll> sz(n+1);
	function<void(ll,ll)> dfs1=[&](ll x,ll fa)->void{
		sz[x]=1;
		for(auto& y:g[x]) if(y!=fa){
			dfs1(y,x);
			sz[x]+=sz[y];
		}
	};
	dfs1(1,0);

	vector<ll> mxsub(n+1);
	function<void(ll,ll)> dfs2=[&](ll x,ll fa)->void{
        mxsub[x]=n-sz[x];
        for (ll y:g[x]) if(y!=fa){
          	dfs2(y,x);
            mxsub[x]=max(mxsub[x],sz[y]);    
        }
	}; 
	dfs2(1,0);

	//##The first method of finding centroids---the size of the largest subtree is the smallest
	// ll mn_mxsub=*min_element(mxsub.begin()+1,mxsub.end());
	// vector<ll> res;
	// for(ll i=1;i<=n;i++){
	// 	if(mxsub[i]==mn_mxsub){
	// 		res.push_back(i);
	// 	}
	// }

	//##The second method of finding centroids---the size of the largest subtree<= n/2
	vector<ll> res;
	for(ll i=1;i<=n;i++){
		if(mxsub[i]<=n/2){
			res.push_back(i);
		}
	}

	return res;
}

//KNOWLEDGE(my unauthentic expressions haha,recorded here)
/*
The definitions and properties of the tree centroid
1.The centroid is such node whose largest subtree's size is the smallest among all nodes;
2.The centroid is such node whose every subtree's size doesn't surpasses the half(floored) of the size of the tree;
3.The centroid is such node when the sum of the length of the path between the node and other nodes is the smallest;

Other properties
4.A tree has at most 2 centroids.If it has 2 centroids,then they are adjacent.
5.If a leaf node is added or deleted,the centroid moved at most across one edge.
6.If two trees are linked,the new centroid is on the path between the two old centroids;
7.If we add edge weights on a non-edge-weighted tree or make an edge-weighted tree a non-edge-weighted one,the centroid(s) remain(s) the same. 
*/

/*
Let's discuss how to improve the authenticity of our expression:
whose largest subtree's size → for which the size of its largest subtree
whose every subtree's size → such that the size of each of its subtrees
surpass half(floored) → exceed half (rounded down) 
is the smallest → is minimized
If it has 2 centroids → In the case where there are two centroids
two trees are linked → two trees are joined together
is on the path → lies on the path
between the two old centroids → connecting the centroids of the two original trees
remain the same → remain unchanged
*/