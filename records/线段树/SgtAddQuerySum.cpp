//https://www.luogu.com.cn/problem/P3372
//@@@
//seg model
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
	ll n;
    vector<ll>& a;
	vector<ll> sum,add;

	segment_tree(vector<ll>& a):a(a){
        n=a.size()-1;
        sum.resize(n<<2);
        add.resize(n<<2);
		build(1,1,n);
    }

	void up(ll p,ll l,ll r){
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}

	void add_update(ll p,ll l,ll r,ll v){
		ll n=r-l+1;
		sum[p]+=n*v;
		add[p]+=v;
	}

	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		ll ln=m-l+1;
		ll rn=r-m;
		if(add[p]){
			add_update(p<<1,l,m,add[p]);
			add_update(p<<1|1,m+1,r,add[p]);
			add[p]=0;
		}
	}

	void build(ll p,ll l,ll r){
        add[p]=0;
		if(l==r){
			sum[p]=a[l];
            return;
		}
		ll m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		up(p,l,r);
	}

	void update(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			add_update(p,l,r,v);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update(p<<1,l,m,x,y,v);
		if(y>m) update(p<<1|1,m+1,r,x,y,v);
		up(p,l,r);
	}

	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return sum[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		ll res=0;
		if(x<=m) res+=query(p<<1,l,m,x,y);
		if(y>m) res+=query(p<<1|1,m+1,r,x,y);
		return res;
	}
};


void solve(){
  ll n,m;
  cin>>n>>m;
  vector<ll> a(n+1);
  for(ll i=1;i<=n;i++){
    cin>>a[i];
  }
  segment_tree seg(a);
  for(ll i=1;i<=m;i++){
    ll op,x,y;
    cin>>op>>x>>y;
    if(op==1){
      ll v;
      cin>>v;
      seg.update(1,1,seg.n,x,y,v);
    }else{
      cout<<seg.query(1,1,seg.n,x,y)<<endl;
    }
  }
}

signed main(){
	ll T=1;
	while(T--){
		solve();
	}
    return 0;
}