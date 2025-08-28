//https://www.luogu.com.cn/problem/P1471
//@@@
//seg
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
	vector<double>& a;
	vector<double> sum,sqsum,add;
	segment_tree(vector<double>& a):a(a){
		n=a.size()-1;
		sum.resize(n<<2);
		sqsum.resize(n<<2);
		add.resize(n<<2);
		build(1,1,n);
	}
	void up(ll p){
		sum[p]=sum[p<<1]+sum[p<<1|1];
		sqsum[p]=sqsum[p<<1]+sqsum[p<<1|1];
	}

	void add_update(ll p,ll l,ll r,double v){
		ll n=r-l+1;
		sqsum[p]+=2*v*sum[p]+n*v*v;
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
			sqsum[p]=a[l]*a[l];
			return;
		}
		ll m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		up(p);
	}
	
	void update(ll p,ll l,ll r,ll x,ll y,double v){
		if(x<=l&&r<=y){
			add_update(p,l,r,v);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update(p<<1,l,m,x,y,v);
		if(y>m) update(p<<1|1,m+1,r,x,y,v);
		up(p);
	}
	
	double query(ll p,ll l,ll r,ll x,ll y,ll op){
		if(x<=l&&r<=y){
			return op==0?sum[p]:sqsum[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		double ans=0;
		if(x<=m) ans+=query(p<<1,l,m,x,y,op);
		if(y>m) ans+=query(p<<1|1,m+1,r,x,y,op);
		return ans; 
	}
	
	double mean(ll x,ll y){
		return 1.0*query(1,1,n,x,y,0)/(y-x+1);
	}
	
	double variance(ll x,ll y){
		double m=mean(x,y);
		double s=query(1,1,n,x,y,0);
		double ss=query(1,1,n,x,y,1);
		return (ss+(y-x+1)*m*m-2*m*s)/(y-x+1);
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<double> a(n+1);
	for(ll i=1;i<=n;i++) cin>>a[i];
	segment_tree seg(a);
	for(ll i=1;i<=m;i++){
		ll op,x,y;
		double k;
		cin>>op>>x>>y;
		if(op==1){
			cin>>k;
			seg.update(1,1,seg.n,x,y,k);
		}else if(op==2){
			cout<<fixed<<setprecision(4)<<seg.mean(x,y)<<" "<<endl;
		}else{
			cout<<fixed<<setprecision(4)<<seg.variance(x,y)<<endl;
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
