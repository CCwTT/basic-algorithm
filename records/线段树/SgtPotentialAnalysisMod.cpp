//https://codeforces.com/contest/438/problem/D
//@@@
//seg,potential analysis
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
    vector<ll> sum,mx;

    segment_tree(vector<ll>& a):a(a){
        n=a.size()-1;
        sum.resize(n<<2);
        mx.resize(n<<2);
        build(1,1,n);
    }

    void up(ll p){
    	sum[p]=sum[p<<1]+sum[p<<1|1];
    	mx[p]=max({mx[p<<1],mx[p<<1|1]});
    }

    void build(ll p,ll l,ll r){
    	if(l==r){
    		sum[p]=mx[p]=a[l];
    		return;
    	}
    	ll m=(l+r)>>1;
    	build(p<<1,l,m);
    	build(p<<1|1,m+1,r);
    	up(p);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
    	if(x<=l&&r<=y){
    		return sum[p];
    	}
    	ll m=(l+r)>>1;
    	ll res=0;
    	if(x<=m) res+=query(p<<1,l,m,x,y);
    	if(y>m) res+=query(p<<1|1,m+1,r,x,y);
    	return res;
    }

    void update_mod(ll p,ll l,ll r,ll x,ll y,ll v){
    	if(mx[p]<v){
    		return;
    	}
    	if(l==r){
    		sum[p]%=v;
    		mx[p]%=v;
    		return;
    	}
    	ll m=(l+r)>>1;
    	if(x<=m) update_mod(p<<1,l,m,x,y,v);
    	if(y>m) update_mod(p<<1|1,m+1,r,x,y,v);
    	up(p);
    }

    void update_rst(ll p,ll l,ll r,ll x,ll v){
    	if(l==r){
    		sum[p]=mx[p]=v;
    		return;
    	}
    	ll m=(l+r)>>1;
    	if(x<=m) update_rst(p<<1,l,m,x,v);
    	else update_rst(p<<1|1,m+1,r,x,v);
    	up(p);
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
	for(ll i=1,op;i<=m;i++){
		cin>>op;
		if(op==1){
			ll x,y;
			cin>>x>>y;
			cout<<seg.query(1,1,seg.n,x,y)<<endl;
		}else if(op==2){
			ll x,y,v;
			cin>>x>>y>>v;
			seg.update_mod(1,1,seg.n,x,y,v);
		}else{
			ll x,v;
			cin>>x>>v;
			seg.update_rst(1,1,seg.n,x,v);
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