//https://www.luogu.com.cn/problem/P1253
//@@@
//sgt
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class SGT{
public:
	ll n;
	vector<ll>& a;
	vector<ll> mx;
	vector<pair<ll,bool>> rst;
	vector<ll> add;

	SGT(vector<ll>& a):a(a){
		n=a.size()-1;
		mx.resize(n<<2);
		rst.resize(n<<2);
		add.resize(n<<2);
		build(1,1,n);
	}
	
	void up(ll p){
		mx[p]=max({mx[p<<1],mx[p<<1|1]});
	} 
	
	void down(ll p){
		if(rst[p].second){
			mx[p<<1]=rst[p].first;
			rst[p<<1]=rst[p];
			add[p<<1]=0;
			mx[p<<1|1]=rst[p].first;
			rst[p<<1|1]=rst[p];
			add[p<<1|1]=0;
			rst[p].second=false;
		}
		if(add[p]){
			mx[p<<1]+=add[p];
			add[p<<1]+=add[p];
			mx[p<<1|1]+=add[p];
			add[p<<1|1]+=add[p];
			add[p]=0;
		}
	}
	
	void build(ll p,ll l,ll r){
		rst[p]={0,false};
		add[p]=0;
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
			mx[p]=v;
			rst[p]={v,true};
			add[p]=0;
			return;
		}
		ll m=l+r>>1;
		down(p);
		if(x<=m) update_rst(p<<1,l,m,x,y,v);
		if(y>m) update_rst(p<<1|1,m+1,r,x,y,v);
		up(p);
	}
	
	void update_add(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			mx[p]+=v;
			add[p]+=v;
			return;
		}
		ll m=l+r>>1;
		down(p);
		if(x<=m) update_add(p<<1,l,m,x,y,v);
		if(y>m) update_add(p<<1|1,m+1,r,x,y,v);
		up(p);
	}
	
	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return mx[p];
		}
		ll m=l+r>>1;
		down(p);
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
	SGT sgt(a);
	for(;Q;Q--){
		ll op;
		cin>>op;
		if(op==1){
			ll l,r,x;
			cin>>l>>r>>x;
			sgt.update_rst(1,1,sgt.n,l,r,x);
		}else if(op==2){
			ll l,r,x;
			cin>>l>>r>>x;
			sgt.update_add(1,1,sgt.n,l,r,x);
		}else{
			ll l,r;
			cin>>l>>r;
			ll res=sgt.query(1,1,sgt.n,l,r);
			cout<<res<<endl;
		}
	}
    return 0;
}