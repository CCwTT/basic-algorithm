//https://www.luogu.com.cn/problem/P2781
//@@@
//dynamic sgt
//abracadabra
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class SGT{
public:
	ll n,tail=1;
	vector<ll> le,ri,sum,add;

	SGT(ll sz):n(sz-1),le(sz),ri(sz),sum(sz),add(sz){}

	void up(ll p,ll l,ll r){
		sum[p]=sum[le[p]]+sum[ri[p]];
	}

	void add_update(ll p,ll l,ll r,ll v){
		ll n=r-l+1;
		sum[p]+=n*v;
		add[p]+=v;
	}
	
	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		if(add[p]){
			if(le[p]==0) le[p]=++tail;
			add_update(le[p],l,m,add[p]);
			if(ri[p]==0) ri[p]=++tail;
			add_update(ri[p],m+1,r,add[p]);
			add[p]=0;
		}
	}
	
	void update(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			add_update(p,l,r,v);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m){
			if(le[p]==0) le[p]=++tail;
			update(le[p],l,m,x,y,v);
		}
		if(y>m){
			if(ri[p]==0) ri[p]=++tail;
			update(ri[p],m+1,r,x,y,v);
		}
		up(p,l,r);
	}
	
	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return sum[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		ll res=0;
		if(x<=m&&le[p]) res+=query(le[p],l,m,x,y);
		if(y>m&&ri[p]) res+=query(ri[p],m+1,r,x,y);
		return res;
	}
};


void solve(){
	ll n,m;
	cin>>n>>m;
	SGT sgt(6*m*(ll)log2(n)+1000);
	ll v;
	for(ll i=0;i<m;i++){
		ll op,x,y;
		cin>>op;
		if(op==1){
			cin>>x>>y>>v;
			sgt.update(1,1,n,x,y,v);
		}else{
			cin>>x>>y;
			cout<<sgt.query(1,1,n,x,y)<<endl;
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
