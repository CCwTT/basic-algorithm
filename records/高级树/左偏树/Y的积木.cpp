//https://www.luogu.com.cn/problem/P2409
//@@@
//leftist tree
//类、结构体指针一定要初始化，不会默认初始化为nullptr
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ltt{
	ll pre;
	ll cost;
	ll idx;
	ll jdx;
	ltt* lc;
	ltt* rc;
	ll dist;
	ltt():pre(0),lc(nullptr),rc(nullptr),dist(0){}
	ltt(ll pre,ll cost,ll idx,ll jdx,ltt* lc,ltt* rc,ll dist):pre(pre),cost(cost),idx(idx),jdx(jdx),lc(lc),rc(rc),dist(dist){}
	ltt* clone(){
		return new ltt(pre,cost,idx,jdx,lc,rc,dist);
	}
};

ll pre(ltt* p) {return p?p->pre:0;}
ll cost(ltt* p) {return p?p->cost:LLONG_MAX/2;}
ll idx(ltt* p) {return p?p->idx:0;}
ll jdx(ltt* p) {return p?p->jdx:0;}
ll dist(ltt* p) {return p?p->dist:-1;}
ltt* lc(ltt* p) {return p?p->lc:nullptr;}
ltt* rc(ltt* p) {return p?p->rc:nullptr;}
ltt* clone(ltt* p) {return p?p->clone():nullptr;}
void set_pre(ltt* p,ll v) {if(p) p->pre=v;}
void set_cost(ltt* p,ll v) {if(p) p->cost=v;}
void set_idx(ltt* p,ll v) {if(p) p->idx=v;}
void set_jdx(ltt* p,ll v) {if(p) p->jdx=v;}
void set_dist(ltt* p,ll v) {if(p) p->dist=v;}
void set_lc(ltt* p,ltt* v) {if(p) p->lc=v;}
void set_rc(ltt* p,ltt* v) {if(p) p->rc=v;}

ltt* merge(ltt* x,ltt* y){
	if(!x||!y) return x?x:y?y:nullptr;
	if(cost(x)>cost(y)) swap(x,y);
	ltt* h=clone(x);
	set_rc(h,merge(rc(h),y));
	if(dist(lc(h))<dist(rc(h))) swap(h->lc,h->rc);
	set_dist(h,dist(rc(h))+1);
	return h;
}

ltt* pop(ltt* x){
	if(!lc(x)||!rc(x)) return clone(lc(x)?lc(x):rc(x));
	return merge(lc(x),rc(x));
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<vector<ll>> a(n+1,vector<ll>());
   	for(ll i=1;i<=n;i++){
   	    ll m;
   	    cin>>m;
		a[i].push_back(0);
   	    for(ll j=1;j<=m;j++){
			ll x;
			cin>>x;
			a[i].push_back(x);
		}
   	}

   	ll first=0;
   	for(ll i=1;i<=n;i++){
   	    sort(a[i].begin()+1,a[i].end());
   	    first+=a[i][1];
   	}

   	auto new_node=[&](ll i,ll j){
			ltt* e=new ltt();
			e->pre=0;
			e->lc=e->rc=nullptr;
			e->idx=i;
			e->jdx=j;
			e->cost=(j+1<a[i].size())?(a[i][j+1]-a[i][j]):LLONG_MAX/2;
			e->dist=0;
			return e;
   	};

   	ltt* root=nullptr;
   	for(ll i=1;i<=n;i++){
		ltt* e=new_node(i,1);
   	    root=merge(root,e);
   	}
   	set_pre(root,first);
   	vector<ll> ans;
   	ans.push_back(first);
   	auto cmp=[&](ltt* i,ltt* j){
   	    return pre(i)+cost(i)>pre(j)+cost(j);
   	};
   	priority_queue<ltt*,vector<ltt*>,decltype(cmp)> pq(cmp);
   	pq.push(root);
   	for(ll i=1;i<k;i++){
   	    ltt* u=pq.top();
		pq.pop();
   	    ans.push_back(pre(u)+cost(u));
   	    ltt* h1=pop(u);
   	    if(h1){
   	        set_pre(h1,pre(u));;
   	        pq.push(h1);
   	    }
   	    if(jdx(u)+1<a[idx(u)].size()){
			ltt* e=new_node(idx(u),jdx(u)+1);;
   	    	ltt* h2=merge(h1,e);
			set_pre(h2,ans.back());
   	    	pq.push(h2);
   	    }
   	}
	
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