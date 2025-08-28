//https://www.lanqiao.cn/problems/1594/learning/
//@@@
//digit dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll helper(ll x){
	vector<vector<vector<vector<vector<ll>>>>> mem(32,vector<vector<vector<vector<ll>>>>(2,vector<vector<vector<ll>>>(2,vector<vector<ll>>(2,vector<ll>(2,-1)))));
    function<ll(ll,bool,bool,bool,bool)> dfs=[&](ll d,bool free1,bool free2,bool ok1,bool ok2)->ll{
		if(!~d) return ok2?1:0;
    	if(~mem[d][free1][free2][ok1][ok2]) return mem[d][free1][free2][ok1][ok2];
    	ll up1=free1?1:(x>>d&1),res=0;
    	for(ll i=0;i<=up1;i++){
    	    ll up2=free2?1:i;
    	    for(ll j=0;j<=up2;j++){
    	        if(!ok1&&!i&&j) continue;
    	        res+=dfs(d-1,free1||i<up1,free2||j<up2,ok1||(j==i&&j==1),ok2||(j==1&&j!=i));
    	    }
    	}
    	return mem[d][free1][free2][ok1][ok2]=res;
	};
	return dfs(__lg(x),false,false,false,false)*3;
}

void solve(){
	ll n;
    cin>>n;
	cout<<helper(n)<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}