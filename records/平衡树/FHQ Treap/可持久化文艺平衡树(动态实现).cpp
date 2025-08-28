//https://www.luogu.com.cn/problem/P5055
//@@@
//balanced tree(fhq-treap)
//所有持久化的操作都标记出来了
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

struct node{
	ll key;
	node* lc;
	node* rc;
	ll sz;
	ll sum;
	ll priority;
	bool rev;
	node(ll key):key(key),lc(nullptr),rc(nullptr),sz(1),sum(key),priority(rnd(1,100000)) {}
};

node* copy(node* p){      //persistent
	if(!p) return nullptr;
	node* q=new node(p->key);
	q->lc=p->lc;
	q->rc=p->rc;
	q->sz=p->sz;
	q->sum=p->sum;
	q->priority=p->priority;
	q->rev=p->rev;
	return q;
}

class FHQ_treap{
public:
	
	vector<node*> root;     //persistent
	FHQ_treap(ll sz):root(sz) {}   //persistent

	ll get_size(node* p){
		return p?p->sz:0;
	}

	ll get_sum(node* p){
		return p?p->sum:0;
	}

	void up(node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+1;
		p->sum=get_sum(p->lc)+get_sum(p->rc)+p->key;
	}

	void down(node* p){
		if(p->rev){
			swap(p->lc,p->rc);
			if(p->lc){
				p->lc=copy(p->lc);   //persistent
				p->lc->rev^=1;
			} 
			if(p->rc){
				p->rc=copy(p->rc);   //persistent
				p->rc->rev^=1;
			} 
			p->rev=false;
		}
	}

	void split(node* p,ll t,node*& l,node*& r){
		if(!p){
			l=r=nullptr;
			return;
		}
		p=copy(p);   //persistent
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
			l=copy(l);   //persistent
			down(l);
			down(l);
			l->rc=merge(l->rc,r);
			up(l);
			return l;
		}else{
			r=copy(r);   //persistent
			down(r);
			r->lc=merge(l,r->lc);
			up(r);
			return r;
		}
	}
};

void solve(){
	ll n;
	cin>>n;
	FHQ_treap fhq(n+1);
	ll last_ans=0;
	for(ll i=1;i<=n;i++){
		ll vs,op;
		ll x,y=0;
		cin>>vs>>op>>x;
		x^=last_ans;
		if(op!=2){
			cin>>y;
			y^=last_ans;
		}
		node* lm=nullptr,*r=nullptr,*l=nullptr,*m=nullptr;
		if(op==1){
			fhq.split(fhq.root[vs],x,l,r);
			auto e=new node(y);
			fhq.root[i]=fhq.merge(fhq.merge(l,e),r);   //persistent
		}else if(op==2){
			fhq.split(fhq.root[vs],x,lm,r);
			fhq.split(lm,x-1,l,m); 
			fhq.root[i]=fhq.merge(l,r);   //persistent
		}else if(op==3){
			fhq.split(fhq.root[vs],y,lm,r);
			fhq.split(lm,x-1,l,m);
			if(m){
				m->rev^=1;
				fhq.root[i]=fhq.merge(fhq.merge(l,m),r);   //persistent
			}else{
				fhq.root[i]=fhq.merge(l,r);   //persistent
			}
		}else{
			fhq.root[i]=fhq.root[vs];       //persistent
			fhq.split(fhq.root[vs],y,lm,r);
			fhq.split(lm,x-1,l,m);
			if(m){
				last_ans=m->sum;
			}else{
				last_ans=0;
			}
			cout<<last_ans<<endl;
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
