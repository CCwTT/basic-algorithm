//https://www.luogu.com.cn/problem/P3391
//@@@
//balanced tree(fhq-treap)
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

const ll MAXN=100001;

ll root=0;
ll cnt=0;
ll key[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];
bool rev[MAXN];
vector<ll> ans;

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void down(ll p){
	if(rev[p]){
		swap(lc[p],rc[p]);
		rev[lc[p]]^=1;
		rev[rc[p]]^=1;
		rev[p]=false;
	}
}

void split(ll p,ll t,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	down(p);
	if(sz[lc[p]]+1<=t){
		l=p;
		split(rc[p],t-sz[lc[p]]-1,rc[l],r);
	}else{
		r=p;
		split(lc[p],t,l,lc[r]);
	}
	up(p);
}

ll merge(ll l,ll r){
	if(!l||!r) return l+r;
	if(priority[l]>=priority[r]){
		down(l);
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		down(r);
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

void inorder(ll p){
	if(!p) return;
	down(p);
	inorder(lc[p]);
	ans.push_back(key[p]);
	inorder(rc[p]);
}

void solve(){
	ll n,m;
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		key[++cnt]=i;
		sz[cnt]=1;
		priority[cnt]=ran(1,100000);
		root=merge(root,cnt);
	}
	for(ll i=1;i<=m;i++){
		ll x,y;
		cin>>x>>y;
		ll lm=0;
		ll r=0;
		split(root,y,lm,r);
		ll l=0;
		ll m=0;
		split(lm,x-1,l,m);
		rev[m]^=1;
		root=merge(merge(l,m),r);
	}
	ans.clear();
	inorder(root);
	for(auto x:ans) cout<<x<<" ";
	cout<<endl;
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
