//https://www.luogu.com.cn/problem/P1253
//@@@
//seg
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
	ll n;
	vector<ll>& a;
	vector<ll> mx,add,rstval;
	vector<bool> rst;
	segment_tree(vector<ll>& a):a(a){
		n=a.size()-1;
		mx.resize(n<<2);
		add.resize(n<<2);
		rst.resize(n<<2);
		rstval.resize(n<<2);
		build(1,1,n);
	}
	
	void up(ll p){
		mx[p]=max({mx[p<<1],mx[p<<1|1]});
	} 

	void rst_update(ll p,ll l,ll r,ll v){
		ll n=r-l+1;
		mx[p]=v;
		rst[p]=true;
		rstval[p]=v;
		add[p]=0;
	}

	void add_update(ll p,ll l,ll r,ll v){
		mx[p]+=v;
		add[p]+=v;
	}
	
	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		if(rst[p]){
			rst_update(p<<1,l,m,rstval[p]);
			rst_update(p<<1|1,m+1,r,rstval[p]);
			rst[p]=false;
		}
		if(add[p]){
			add_update(p<<1,l,m,add[p]);
			add_update(p<<1|1,m+1,r,add[p]);
			add[p]=0;
		}
	}
	
	void build(ll p,ll l,ll r){
		if(l==r){
			mx[p]=a[l];
			return;
		}
		ll m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		up(p);
	}
	
	void update_rst(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			rst_update(p,l,r,v);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update_rst(p<<1,l,m,x,y,v);
		if(y>m) update_rst(p<<1|1,m+1,r,x,y,v);
		up(p);
	}
	
	void update_add(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			add_update(p,l,r,v);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update_add(p<<1,l,m,x,y,v);
		if(y>m) update_add(p<<1|1,m+1,r,x,y,v);
		up(p);
	}
	
	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return mx[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		ll res=LLONG_MIN/2;
		if(x<=m) res=max({res,query(p<<1,l,m,x,y)});
		if(y>m) res=max({res,query(p<<1|1,m+1,r,x,y)});
		return res;
	}
};


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n,Q;
	cin>>n>>Q;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	segment_tree seg(a);
	for(;Q;Q--){
		ll op;
		cin>>op;
		if(op==1){
			ll l,r,x;
			cin>>l>>r>>x;
			seg.update_rst(1,1,seg.n,l,r,x);
		}else if(op==2){
			ll l,r,x;
			cin>>l>>r>>x;
			seg.update_add(1,1,seg.n,l,r,x);
		}else{
			ll l,r;
			cin>>l>>r;
			ll res=seg.query(1,1,seg.n,l,r);
			cout<<res<<endl;
		}
	}
    return 0;
}