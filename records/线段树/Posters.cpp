//https://www.luogu.com.cn/problem/P3740
//@@@
//seg,dicretization
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
	vector<ll> poster;
	vector<bool> vis;
	segment_tree(ll sz):n(sz-1){
		poster.resize(sz<<2);
		vis.resize(sz<<2);
	}

	void down(ll p){
		if(poster[p]){
			poster[p<<1]=poster[p];
			poster[p<<1|1]=poster[p];
			poster[p]=0;
		}
	}

	void update(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			poster[p]=v;
			return;
		}
		ll m=l+r>>1;
		down(p);
		if(x<=m) update(p<<1,l,m,x,y,v);
		if(y>m) update(p<<1|1,m+1,r,x,y,v);
	}

	ll query(ll p,ll l,ll r,ll x,ll y){
		if(l==r){
			if(poster[p]&&!vis[poster[p]]){
				vis[poster[p]]=true;
				return 1;
			}else{
				return 0;
			}
		}
		ll m=l+r>>1;
		down(p);
		ll res=0;
		if(x<=m) res+=query(p<<1,l,m,x,y);
		if(y>m) res+=query(p<<1|1,m+1,r,x,y);
		return res;
	}
};

class Discretizer{
public:
	vector<ll> disc;
	Discretizer() {}

	void insert(ll x){
		disc.push_back(x);
	}

	ll discretize(){
        sort(disc.begin(),disc.end());
		disc.erase(unique(disc.begin(),disc.end()),disc.end());
		return disc.size();
	}

	ll query(ll x){
		return lower_bound(disc.begin(),disc.end(),x)-disc.begin()+1;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	Discretizer disc;
	vector<ll> pl(m+1),pr(m+1);
	for(ll i=1;i<=m;i++){
		cin>>pl[i]>>pr[i];
		disc.insert(pl[i]);
		disc.insert(pr[i]);
	} 
	ll sz=disc.discretize();
	for(ll i=1;i<sz;i++){
		if(disc.disc[i]-disc.disc[i-1]>1){
			disc.insert(disc.disc[i]-1);
		}
	}
	ll N=disc.discretize();
	segment_tree seg(N+1);
	for(ll i=1,x,y;i<=m;i++){
		x=disc.query(pl[i]);
		y=disc.query(pr[i]);
		seg.update(1,1,seg.n,x,y,i);
	}
	cout<<seg.query(1,1,seg.n,1,disc.query(n))<<endl;
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
