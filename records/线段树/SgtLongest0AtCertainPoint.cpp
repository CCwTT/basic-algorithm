//https://www.luogu.com.cn/problem/P1503
//@@@
//seg interval coalescing
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
	ll n;
	vector<ll> pre0,suf0;
	segment_tree(ll sz):n(sz-1),pre0(sz<<2),suf0(sz<<2) {
		build(1,1,n);
	}

	void up(ll p,ll l,ll r){
		ll m=l+r>>1;
		ll ln=m-l+1;
		ll rn=r-m;
		pre0[p]=pre0[p<<1]==ln?ln+pre0[p<<1|1]:pre0[p<<1];
		suf0[p]=suf0[p<<1|1]==rn?rn+suf0[p<<1]:suf0[p<<1|1];
	}

	void build(ll p,ll l,ll r){
		if(l==r){
			pre0[p]=suf0[p]=1;
			return;
		}
		ll m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		up(p,l,r);
	}
	
	void update(ll p,ll l,ll r,ll x,ll v){
		if(l==r){
			pre0[p]=suf0[p]=v==0;
			return;
		}
		ll m=l+r>>1;
		if(x<=m) update(p<<1,l,m,x,v);
		else update(p<<1|1,m+1,r,x,v);
		up(p,l,r);
	}
	
	ll query(ll p,ll l,ll r,ll x){
		if(l==r){
			return pre0[p];
		}
		ll m=l+r>>1;
		if(x<=m){
			if(x>m-suf0[p<<1]) return suf0[p<<1]+pre0[p<<1|1];
			else return query(p<<1,l,m,x);
		}else{
			if(x<m+1+pre0[p<<1|1]) return suf0[p<<1]+pre0[p<<1|1];
			else return query(p<<1|1,m+1,r,x);
		}
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	segment_tree seg(n+1);
	stack<ll> stk;
	string op;
	for(ll i=1;i<=m;i++){
		cin>>op;
		if(op=="D"){
			ll x;
			cin>>x;
			seg.update(1,1,seg.n,x,1);
			stk.push(x);
		}else if(op=="R"){
			auto x=stk.top();
			stk.pop();
			seg.update(1,1,seg.n,x,0);
		}else{
			ll x;
			cin>>x;
			cout<<seg.query(1,1,seg.n,x)<<endl;
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
