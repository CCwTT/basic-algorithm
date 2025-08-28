//https://atcoder.jp/contests/abc398/tasks/abc398_e
//bipartite graph,dfs coloring,STL,state compression
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	ll n;
    cin>>n;
    vector<unordered_set<ll>> g(n+1);
    for(ll i=0;i<n-1;i++){
        ll u,v;
        cin>>u>>v;
        g[u].insert(v);
        g[v].insert(u);
    }
    vector<unordered_set<ll>> A(2);
    vector<bool> vis(n+1,false);

    function<void(ll,ll,ll)> dfs=[&](ll x,ll fa,ll c)->void{
        vis[x]=true;
        A[c].insert(x);
        for(auto y:g[x]) if(y!=fa){
            if(!vis[y]){
                dfs(y,x,1-c);
            }
        }
    };
    dfs(1,0,0);
    unordered_set<ll> B;
    for(auto x:A[0]){
        for(auto y:A[1]){
            if(!g[x].count(y)){
                ll mn=min(x,y);
                ll mx=max(x,y);
                B.insert((mn<<16)|mx);
            }
        }
    }
    if(B.size()&1){
        cout<<"First"<<endl;
        while(true){
            auto xy=*B.begin();
            ll x=xy>>16;
            ll y=xy&0xffff;
            B.erase(B.begin());
            cout<<x<<" "<<y<<endl;
            cin>>x>>y;
            if(!~x&&!~y) exit(0);
            B.erase((x<<16)|y);
        }
    }else{
        cout<<"Second"<<endl;
        while(true){
            ll x,y;
            cin>>x>>y;
            if(!~x&&!~y) exit(0);
            B.erase((x<<16)|y);
            auto xy=*B.begin();
            x=xy>>16;
            y=xy&0xffff;
            B.erase(B.begin());
            cout<<x<<" "<<y<<endl;
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
