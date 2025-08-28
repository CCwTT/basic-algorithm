//https://www.luogu.com.cn/problem/P2184
//@@@
//seg
//The main logic is skilful
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
	vector<ll> sum;
	segment_tree(ll sz):n(sz-1),sum(sz<<2,0){}

	void up(ll p){
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}
	
	void update(ll p,ll l,ll r,ll x,ll v){
		if(l==r){
			sum[p]+=v;
			return;
		}
		ll m=(l+r)>>1;
		if(x<=m) update(p<<1,l,m,x,v);
		else update(p<<1|1,m+1,r,x,v);
		up(p);
	}
	
	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return sum[p];
		}
		ll m=l+r>>1;
		ll res=0;
		if(x<=m) res+=query(p<<1,l,m,x,y);
		if(y>m) res+=query(p<<1|1,m+1,r,x,y);
		return res;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	segment_tree seg1(n+1),seg2(n+1);
	for(ll i=1,op,x,y;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1){
			seg1.update(1,1,seg1.n,x,1);
			seg2.update(1,1,seg2.n,y,1);
		}else{
			ll s=seg1.query(1,1,seg1.n,1,y);
			ll e=x==1?0:seg2.query(1,1,seg2.n,1,x-1);
			cout<<s-e<<endl;
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
