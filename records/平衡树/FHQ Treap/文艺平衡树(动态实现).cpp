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
ll rnd(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

class FHQ_treap{
public:
	struct node{
		ll key;
		node* lc;
		node* rc;
		ll sz;
		ll priority;
		bool rev;
		node(ll key):key(key),lc(nullptr),rc(nullptr),sz(1),priority(rnd(1,100000)) {}
	};
	node* root=nullptr;

	ll get_size(node* p){
		return p?p->sz:0;
	}

	void up(node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+1;
	}

	void down(node* p){
		if(p->rev){
			swap(p->lc,p->rc);
			if(p->lc) p->lc->rev^=1;
			if(p->rc) p->rc->rev^=1;
			p->rev=false;
		}
	}

	void split(node* p,ll t,node*& l,node*& r){
		if(!p){
			l=r=nullptr;
			return;
		}
		down(p);
		if(get_size(p->lc)+1<=t){
			l=p;
			split(p->rc,t-get_size(p->lc)-1,l->rc,r);
		}else{
			r=p;
			split(p->lc,t,l,r->lc);
		}
		up(p);
	}

	node* merge(node* l,node* r){
		if(!l||!r) return l?l:r?r:nullptr;
		if(l->priority>=r->priority){
			down(l);
			l->rc=merge(l->rc,r);
			up(l);
			return l;
		}else{
			down(r);
			r->lc=merge(l,r->lc);
			up(r);
			return r;
		}
	}

	vector<ll> inorder(node* rt){
		vector<ll> res;
		function<void(node*)> dfs=[&](node* p)->void{
			if(!p) return;
			down(p);
			dfs(p->lc);
			res.push_back(p->key);
			dfs(p->rc);
		};
		dfs(rt);
		return res;
	}
};

void solve(){
	FHQ_treap fhq;
	ll n,K;
	cin>>n>>K;
	for(ll i=1;i<=n;i++){
		auto e=new FHQ_treap::node(i);
		fhq.root=fhq.merge(fhq.root,e);
	}
	for(ll i=1;i<=K;i++){
		ll x,y;
		cin>>x>>y;
		FHQ_treap::node* lm=nullptr;
		FHQ_treap::node* r=nullptr;
		fhq.split(fhq.root,y,lm,r);
		FHQ_treap::node* l=nullptr;
		FHQ_treap::node* m=nullptr;
		fhq.split(lm,x-1,l,m);
		m->rev^=1;
		fhq.root=fhq.merge(fhq.merge(l,m),r);
	}
	auto ans=fhq.inorder(fhq.root);
	for(auto& x:ans) cout<<x<<" ";
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
