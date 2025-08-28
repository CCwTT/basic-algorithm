//https://www.luogu.com.cn/problem/P3835
//@@@
//balanced tree(fhq-treap)

//总结一下静态方法和动态方法,静态结构体方法和静态多数组方法的优劣:
/*
静态方法:
优点:(1)单例模式下更加方便;(2)没有空指针异常的隐患;
缺点:(1)不适合多例模式;(2)需要预估空间大小
动态方法:
优点:(1)适合多例模式;(2)不需要预估空间大小
缺点:(1)有空指针异常的隐患,书写也更加复杂

静态结构体方法:
优点:(1)书写形式和动态方法很像,书写顺序是顺序
缺点:(2)书写量上比较大

静态多数组方法:
优点:(1)书写量比较小
缺点:(1)书写顺序是逆序
*/

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
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
	ll priority;
	node(ll key=0):key(key),lc(nullptr),rc(nullptr),sz(1),priority(rnd(1,100000)){}
};

node* copy(node* p){
	node* q=new node;
	q->key=p->key;
	q->lc=p->lc;
	q->rc=p->rc;
	q->sz=p->sz;
	q->priority=p->priority;
	return q;
}

class persistent_FHQ_treap{
public:
	vector<node*> root;
	persistent_FHQ_treap(ll sz):root(sz) {}

	ll get_size(node* p){
		return p?p->sz:0;
	}

	void up(node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+1;
	}

	void split(node* p,ll t,node*& l,node*& r){
		if(!p){
			l=r=nullptr;
			return;
		}
		p=copy(p);
		if(p->key<=t){
			l=p;
			split(p->rc,t,l->rc,r);
		}else{
			r=p;
			split(p->lc,t,l,r->lc);
		}
		up(p);
	}

	node* merge(node* l,node* r){
		if(!l||!r) return l?l:r?r:nullptr;
		if(l->priority>=r->priority){
			l=copy(l);
			l->rc=merge(l->rc,r);
			up(l);
			return l;
		}else{
			r=copy(r);
			r->lc=merge(l,r->lc);
			up(r);
			return r;
		}
	}

	void insert(node* p,ll k,ll vs){
		node* l=nullptr;
		node* r=nullptr;
		split(p,k,l,r);
		node* e=new node(k);
		root[vs]=merge(merge(l,e),r);
	}

	void remove(node* p,ll k,ll vs){
		node* lm=nullptr;
		node* r=nullptr;
		split(p,k,lm,r);
		node* l=nullptr;
		node* m=nullptr;
		split(lm,k-1,l,m);
		if(m){
			root[vs]=merge(merge(l,merge(m->lc,m->rc)),r);
		}else{
			root[vs]=p;
		}
	}

	ll small(node* p,ll k){
		if(!p) return 0;
		if(k<=p->key) return small(p->lc,k);
		return get_size(p->lc)+1+small(p->rc,k);
	}

	ll get_rank(node* p,ll k){
		return small(p,k)+1;
	}

	ll at(node* p,ll x){
		if(x<=get_size(p->lc)) return at(p->lc,x);
		if(x<=get_size(p->lc)+1) return p->key;
		return at(p->rc,x-get_size(p->lc)-1);
	}

	ll prev(node* p,ll k){
		if(!p) return INT_MIN+1;
		if(k<=p->key) return prev(p->lc,k);
		return max(p->key,prev(p->rc,k));
	}

	ll next(node* p,ll k){
		if(!p) return INT_MAX;
		if(k>=p->key) return next(p->rc,k);
		return min(p->key,next(p->lc,k));
	}
};

void solve(){
	ll n;
	cin>>n;
	persistent_FHQ_treap fhq(n+1);
	for(ll i=1;i<=n;i++){
		ll vs,op,x;
		cin>>vs>>op>>x;
		if(op==1){
			fhq.insert(fhq.root[vs],x,i);
		}else if(op==2){
			fhq.remove(fhq.root[vs],x,i);
		}else{
			fhq.root[i]=fhq.root[vs];
			if(op==3){
				cout<<fhq.get_rank(fhq.root[i],x)<<endl;
			}else if(op==4){
				cout<<fhq.at(fhq.root[i],x)<<endl;
			}else if(op==5){
				cout<<fhq.prev(fhq.root[i],x)<<endl;
			}else{
				cout<<fhq.next(fhq.root[i],x)<<endl;
			}
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
