//https://www.luogu.com.cn/problem/P8051
//@@@
//seg,dp
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
	vector<ll> mx;
	segment_tree(ll sz):n(sz-1),mx(n<<2){}

	void up(ll p,ll l,ll r){
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
	}

	void update(ll p,ll l,ll r,ll x,ll v){
		if(l==r){
			mx[p]=v;
			return;
		}
		ll m=l+r>>1;
		if(x<=m) update(p<<1,l,m,x,v);
		else update(p<<1|1,m+1,r,x,v);
		up(p,l,r);
	}

	void update(ll x,ll v){
		update(1,1,n,x,v);
	}

	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y) return mx[p];
		ll res=LLONG_MIN;
		ll m=l+r>>1;
		if(x<=m) res=max(res,query(p<<1,l,m,x,y));
		if(y>m) res=max(res,query(p<<1|1,m+1,r,x,y));
		return res; 
	}

	ll query(ll x,ll y){
		if(x<=y) return query(1,1,n,x,y);
		return -1;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	vector<ll> lnr(n+2),rnr(n+2);
	stack<ll> stk;
	for(ll i=1;i<=n;i++){
		while(!stk.empty()&&a[stk.top()]<a[i]){
			stk.pop();
		}
		lnr[i]=stk.empty()?0:stk.top();
		stk.push(i);
	}
	stack<ll>().swap(stk);
	for(ll i=n;i>=1;i--){
		while(!stk.empty()&&a[stk.top()]<a[i]){
			stk.pop();
		}
		rnr[i]=stk.empty()?n+1:stk.top();
		stk.push(i);
	}
	vector<ll> f(n+1);
	segment_tree seg(n+1);
	vector<ll> indices(n+1);
	iota(indices.begin(),indices.end(),0);
	sort(indices.begin()+1,indices.end(),[&](ll i,ll j){
		return a[i]<a[j];
	});
	for(ll i0=1;i0<=n;i0++){
		ll i=indices[i0];
		f[i]=max(seg.query(lnr[i]+1,i-1),seg.query(i+1,rnr[i]-1))+1;
		seg.update(i,f[i]);
	}
	//Log(f);
	ll ans=f[1];
	map<ll,ll> mp;
	for(ll i=1;i<=n;i++){
		if(!mp.count(a[i])||f[i]>mp[a[i]]){
			mp[a[i]]=f[i];
		}
	}
	for(auto it=next(mp.begin());it!=mp.end();it++){
		it->second=max(it->second,prev(it)->second);
	}
	for(ll i=0;i<m;i++){
		ll x;
		cin>>x;
		auto it=mp.upper_bound(x);
		if(it==mp.begin()) continue;
		it--;
		ans+=it->second;
	}
	cout<<ans<<endl;
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
