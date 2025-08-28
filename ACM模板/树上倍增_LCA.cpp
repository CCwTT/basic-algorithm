#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//class LCA{
//    int n;
//    vector<int> fa;
//    vector<int> depth; 
//    
//    LCA(vector<int>& fa){
//    	this->n=fa.size();
//    	this->fa=fa;
//    	this->depth=getdepth();
//	}
//	
//	vector<int> getdepth(){
//		vector<int> depth(n,0);
//		function<void(int,int)> dfs=[&](int x)->void{
//			for(auto y:)
//		};
//	}
//    
//    //�ڵ���0~n-1,root=0
//    vector<vector<int>> getst(){
//    	int m=32-__builtin_clz(n-1);
//    	vector<vector<int>> st(n,vector<int>(m,-1));
//    	for(int i=0;i<n;i++){
//    		st[i][0]=fa[i];
//    	}
//    	for(int i=1;i<m;i++){
//    		for(int x=0;x<n;x++){
//    			if(~st[x][i-1]){
//    				st[x][i]=st[st[x][i-1]][i-1];
//    			}
//    		}
//    	}
//    	return st;
//    }
//    
//    //int get_kth_ancestor(int x,int k){
//    //	if(k>n-1) return -1;
//    //	int m=32-__builtin_clz(k);
//    //	for(int i=0;i<m;i++){
//    //		if(k>>i&1){
//    //			if(!~st[x][i-1]) break;
//    //			x=st[x][i-1];
//    //		}
//    //	}
//    //	return x;
//    //} 
//    
//    //���д��
//    int get_kth_ancestor(int x,int k){
//    	for(;k&&~x;k&=k-1){
//    		x=st[x][__builtin_ctz(k)];
//    	}
//    	return x;
//    } 
//    
//    int lca(int x,int y){
//    
//    }
//};

//(��) 
class Info{
public:
	vector<ll> depth;
	vector<vector<ll>> st;

	Info(vector<pair<ll,ll>>& edges){
		ll n=edges.size()+1;
		//�����m���ó�__lg(n-1)+1�ǲ���׳��,����������ǵ��ڵ㣬�ͻ������� 
		ll high=__lg(n);
		vector<vector<ll>> g(n);
		for(auto [x,y]:edges){
			g[x].push_back(y);
			g[y].push_back(x);
		}
		depth.resize(n);
		st.resize(n,vector<ll>(high+1,-1));
		function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
			st[x][0]=fa;
			for(ll j=1;j<=high;j++){
				if(~st[x][j-1]){
					st[x][j]=st[st[x][j-1]][j-1];
				}
			}
			for(auto y:g[x]) if(y!=fa){
				depth[y]=depth[x]+1;
				dfs(y,x);
			}
		}; 
		dfs(0,-1);
	}
	
	ll get_kth_ancestor(ll x,ll k){
		for(;k&&~x;k&=k-1){
			x=st[x][__builtin_ctzll(k)];
		}
		return x;
	}
	
	ll lca(ll x,ll y){
		if(depth[y]>depth[x]) swap(x,y);
		x=get_kth_ancestor(x,depth[x]-depth[y]);
		if(x==y){
			return x;
		}
		for(ll i=st[x].size()-1;i>=0;i--){
			if(st[x][i]!=st[y][i]){
				x=st[x][i];
				y=st[y][i];
			}
		}
		return st[x][0];
	} 
};

//1-indexed,use the good loop property in the 0 index
class Info{
public:
	vector<ll> depth;
	vector<vector<ll>> st;

	Info(vector<vector<ll>>& g){
		ll n=g.size()-1;
		//�����high�ó�__lg(n-1)�ǲ���׳��,����������ǵ��ڵ㣬�ͻ������� 
		ll high=__lg(n); //n-0
		depth.assign(n+1,0);
		st.assign(n+1,vector<ll>(high+1,0));
		function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
			depth[x]=depth[fa]+1;
			st[x][0]=fa;
			for(ll j=1;j<=high;j++){
				st[x][j]=st[st[x][j-1]][j-1];
			}
			for(auto y:g[x]) if(y!=fa){
				dfs(y,x);
			}
		}; 
		dfs(1,0);
	}
	
	ll get_kth_ancestor(ll x,ll k){
		for(;k;k&=k-1){
			x=st[x][__builtin_ctzll(k)];
		}
		return x;
	}
	
	ll __lca(ll x,ll y){
		if(depth[x]>depth[y]) swap(x,y);
		y=get_kth_ancestor(y,depth[y]-depth[x]);
		if(x==y){
			return x;
		}
		for(ll j=st[0].size()-1;j>=0;j--){
			if(st[x][j]!=st[y][j]){
				x=st[x][j];
				y=st[y][j];
			}
		}
		return st[x][0];
	} 
};

//@@@
//https://www.lanqiao.cn/problems/3506/learning/?isWithAnswer=true
class Info{
public:
	vector<ll> depth;
	vector<vector<ll>> stjump,st;
	Info() {}
	Info(vector<vector<pair<ll,ll>>>& g){
		ll n=g.size()-1;
		ll high=__lg(n);
		depth.assign(n+1,0);
		stjump.assign(n+1,vector<ll>(high+1));
		st.assign(n+1,vector<ll>(high+1,0));
		function<void(ll,ll,ll)> dfs=[&](ll x,ll fa,ll w)->void{
			depth[x]=depth[fa]+1;
			stjump[x][0]=fa;
			for(ll j=1;j<=high;j++){
				stjump[x][j]=stjump[stjump[x][j-1]][j-1];
			}
			st[x][0]=w;
			for(ll j=1;j<=high;j++){
				st[x][j]=min(st[x][j-1],st[stjump[x][j-1]][j-1]);
			}
			for(auto& [w,y]:g[x]) if(y!=fa){
				dfs(y,x,w);
			}
		};
		dfs(1,0,0);
	}
	
	ll get_kth_ancestor(ll x,ll k){
		for(;k;k&=k-1){
			x=stjump[x][__builtin_ctzll(k)];
		}
		return x;
	}
	
	ll __lca(ll x,ll y){
		if(depth[x]>depth[y]) swap(x,y);
		y=get_kth_ancestor(y,depth[y]-depth[x]);
		if(x==y) return x;
		for(ll j=st[0].size()-1;j>=0;j--){
			if(stjump[x][j]!=stjump[y][j]){
				x=stjump[x][j];
				y=stjump[y][j];
			}
		}
		return stjump[x][0];
	}
	
	ll get(ll x,ll k){
		ll res=LLONG_MAX/2;
		for(;k;k&=k-1){
			res=min(res,st[x][__builtin_ctzll(k)]);
			x=stjump[x][__builtin_ctzll(k)];
		}
		return res;
	}
	
	ll query(ll x,ll y){
		ll lca=__lca(x,y);
		return min(get(x,depth[x]-depth[lca]),get(y,depth[y]-depth[lca]));
	}
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}
