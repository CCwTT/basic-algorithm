//https://www.luogu.com.cn/problem/P3369#submit
//@@@
//balanced tree(splay)
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

struct node{
	ll key;
	node* lc;
	node* rc;
	node* fa;
	ll sz;
	node(ll key):key(key),lc(nullptr),rc(nullptr),fa(nullptr),sz(1) {}
};

class splay_tree{
public:
	node* root=nullptr;
	
	ll get_size(node* p){
		return p?p->sz:0;
	}

	node* get_fa(node* p){
		return p?p->fa:nullptr;
	}
	
	void up(node* p){
		if(!p) return;
		p->sz=get_size(p->lc)+get_size(p->rc)+1;
	}	

	ll side(node* p){
		return !p->fa?0:p->fa->lc==p?0:1;
	}

	void rotate(node* p){
		node* f=get_fa(p),*g=get_fa(f);
		if(side(p)==0){
			if(f) f->lc=p->rc;
			if(f&&f->lc) f->lc->fa=f;
			p->rc=f;
		}else{
			if(f) f->rc=p->lc;
			if(f&&f->rc) f->rc->fa=f;
			p->lc=f;
		}
		if(g){
			if(side(f)==0){
				g->lc=p;
			}else{
				g->rc=p;
			}
		}
		if(f) f->fa=p;
		if(p) p->fa=g;
		up(f);
		up(p);
	}

	void splay(node* p,node* tar){
		node* f=get_fa(p),*g=get_fa(f);
		while(f!=tar){
			if(g!=tar){
				if(side(p)==side(f)){
					rotate(f);
				}else{
					rotate(p);
				}
			}
			rotate(p);
			f=get_fa(p);
			g=get_fa(f);
		}
		if(!tar){
			root=p;
		}
	}

	node* node_at(ll rk){
		node* p=root;
		while(p){
			if(rk<=get_size(p->lc)){
				p=p->lc;
			}else if(rk<=get_size(p->lc)+1){
				return p;
			}else{
				rk-=get_size(p->lc)+1;
				p=p->rc;
			}
		}
		return nullptr;
	}

	void insert(ll k){
		node* e=new node(k);
		if(!root){
			root=e;
			return;
		}
		node* f=nullptr,*p=root;
		ll sd=0;
		while(p){
			f=p;
			if(k<=p->key){
				sd=0;
				p=p->lc;
			}else{
				sd=1;
				p=p->rc;
			}
		}
		if(sd==0){
			f->lc=e;
		}else{
			f->rc=e;
		}
		e->fa=f;
		splay(e,nullptr);
	}

	ll get_rank(ll k){
		node* p=root,*pp=root;
		ll res=0;
		while(p){
			pp=p;
			if(k<=p->key){
				p=p->lc;
			}else{
				res+=get_size(p->lc)+1;
				p=p->rc;
			}
		}
		splay(pp,nullptr);
		return res+1;
	}

	ll at(ll x){
		node* p=node_at(x);
		splay(p,nullptr);
		return p->key;
	}

	ll prev(ll k){
		node* p=root,*pp=root;
		ll res=LLONG_MIN;
		while(p){
			pp=p;
			if(k<=p->key){
				p=p->lc;
			}else{
				res=max(res,p->key);
				p=p->rc;
			}
		}
		splay(pp,nullptr);
		return res;
	}

	ll next(ll k){
		node* p=root,*pp=root;
		ll res=LLONG_MAX;
		while(p){
			pp=p;
			if(k>=p->key){
				p=p->rc;
			}else{
				res=min(res,p->key);
				p=p->lc;
			}
		}
		splay(pp,nullptr);
		return res;
	}

	void remove(ll k){
		ll rk=get_rank(k);
		if(rk==get_rank(k+1)) return;
		node* p=node_at(rk);
		splay(p,nullptr);
		if(!p->lc){
			root=p->rc;
		}else if(!p->rc){
			root=p->lc;
		}else{
			node* q=node_at(rk+1);
			splay(q,p);
			if(q){
				q->lc=p->lc;
				if(q->lc) q->lc->fa=q;
				up(q);
			}
			root=q;
		}
		if(root){
			root->fa=nullptr;
		}
	}
};

void solve(){
	ll n;
	cin>>n;
	splay_tree splay;
	for(ll i=0;i<n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			splay.insert(x);
		}else if(op==2){
			splay.remove(x);
		}else if(op==3){
			cout<<splay.get_rank(x)<<endl;
		}else if(op==4){
			cout<<splay.at(x)<<endl;
		}else if(op==5){
			cout<<splay.prev(x)<<endl;
		}else{
			cout<<splay.next(x)<<endl;
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
