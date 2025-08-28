class TreeAncestor {
    typedef long long ll;
    vector<ll> depth;
    vector<vector<ll>> st;

public:
    TreeAncestor(int n, vector<int>& parent) {
		//这里把m设置成__lg(n-1)+1是不健壮的,如果整棵树是单节点，就会有问题 
		ll m=__lg(n)+1;
		vector<vector<ll>> g(n);
		for(ll i=1;i<parent.size();i++){
            g[i].push_back(parent[i]);
            g[parent[i]].push_back(i);
        }
		depth.resize(n);
		st.resize(n,vector<ll>(m,-1));
		function<void(ll,ll)> dfs=[&](ll x,ll fa)->void{
			st[x][0]=fa;
            for(ll i=1;i<m;i++){
                if(~st[x][i-1]){
                    st[x][i]=st[st[x][i-1]][i-1];
                }
            }
			for(auto y:g[x]) if(y!=fa){
				depth[y]=depth[x]+1;
				dfs(y,x);
			}
		}; 
		dfs(0,-1);
    }
    
    ll getKthAncestor(ll x,ll k){
		for(;k&&~x;k&=k-1){
			x=st[x][__builtin_ctzll(k)];
		}
		return x;
	}
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */