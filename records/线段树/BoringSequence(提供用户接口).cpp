//https://www.luogu.com.cn/problem/P1438
//@@@
//seg,difference
//link:/ABC/ABC407/F-SumsOfSlidingWindowMaximum(单调栈,线段树)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

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

	void user_update(ll x,ll y,ll k,ll d){
		update(1,1,n,x,x,k);
		if(y-x>=1){
			update(1,1,n,x+1,y,d);
		}
		if(y+1<=n){
			update(1,1,n,y+1,y+1,-(k+(y-x)*d));
		}
	}

	ll user_query(ll x){
		return query(1,1,n,1,x);
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1),diff(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	diff[1]=a[1];
	for(ll i=2;i<=n;i++){
		diff[i]=a[i]-a[i-1];
	}
	segment_tree seg(diff);
	for(ll i=0;i<m;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll x,y,k,d;
			cin>>x>>y>>k>>d;
			seg.user_update(x,y,k,d);
		}else{
			ll x;
			cin>>x;
			cout<<seg.user_query(x)<<endl;
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