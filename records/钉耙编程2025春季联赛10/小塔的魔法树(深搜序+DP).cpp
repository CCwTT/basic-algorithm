//https://acm.hdu.edu.cn/contest/problem?cid=1159&pid=1007
//@@@
//dfn,dp
//ka chang so no solve()
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll mod=1e9+7;

signed main(){
    ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        ll n,m;
        cin>>n>>m;
	    vector<ll> a(n+1);
	    vector<vector<ll>> g(n+1);
        for(ll i=1;i<=n;i++) cin>>a[i];
        for(ll i=1;i<n;i++){
            ll u,v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

	    vector<ll> dfn(n+1),R(n+1),idx(n+1);
	    ll cnt=0;
	    function<void(ll,ll)> dfs=[&](ll u,ll fa){
	        dfn[u]=R[u]=++cnt;
	        idx[cnt]=u;
	        for(ll v:g[u]) if(v!=fa){
	            dfs(v,u);
	            R[u]=max(R[u],R[v]);
	        }
	    };
        dfs(1,0);
	    vector<vector<ll>> f(n+2,vector<ll>(m+1,0));
        f[1][0]=1;
        for(ll i=1;i<=n;i++){
	    	for(ll j=0;j<=m;j++){
                if(j+a[idx[i]]<=m){
                    f[i+1][j+a[idx[i]]]=(f[i+1][j+a[idx[i]]]+f[i][j])%mod;
	    		}
                if(i!=1){
	    			f[R[idx[i]]+1][j]=(f[R[idx[i]]+1][j]+f[i][j])%mod;
	    		}
            }
	    }
        ll ans=0;
        for(ll i=0;i<=m;i++){
            ans=(ans+f[n+1][i])%mod;
	    }
        cout<<ans<<endl;  
    }
    return 0;
}