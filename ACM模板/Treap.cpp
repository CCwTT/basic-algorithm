class treap{
public:
	struct node{
		ll key;
		ll val;
		node* lc;
		node* rc;
		ll sz;
		ll priority;
		node(){}
		node(ll k):key(k),val(1),lc(nullptr),rc(nullptr),sz(1),priority(ran(1,100000)) {}
	};

	node* root=nullptr;

	ll get_size(node* p){
		return p?p->sz:0;
	}

	ll get_priority(node* p){
		return p?p->priority:0;
	}

	void up(node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+p->val;
	}

	node* left_rotate(node* p){
		node* tmp=p->rc;
		p->rc=tmp->lc;
		tmp->lc=p;
		up(p);
		up(tmp);
		return tmp;
	}

	node* right_rotate(node* p){
		node* tmp=p->lc;
		p->lc=tmp->rc;
		tmp->rc=p;
		up(p);
		up(tmp);
		return tmp;
	}

	node* insert(node* p,ll k){
		if(!p){
			return new node(k);
		}
		if(k==p->key){
			p->val++;
		}else if(k<p->key){
			p->lc=insert(p->lc,k);
		}else{
			p->rc=insert(p->rc,k);
		}
		up(p);
		if(p->lc&&p->lc->priority>p->priority){
			return right_rotate(p);
		}
		if(p->rc&&p->rc->priority>p->priority){
			return left_rotate(p);
		}
		return p;
	}

	void insert(ll k){
		root=insert(root,k);
	}

	ll small(node* p,ll k){
		if(!p){
			return 0;
		}
		if(k<=p->key){
			return small(p->lc,k);
		}else{
			return get_size(p->lc)+p->val+small(p->rc,k);
		}
	}

	ll get_rank(ll k){
		return small(root,k)+1;
	}

	ll at(node* p,ll x){
		if(x<=get_size(p->lc)){
			return at(p->lc,x);
		}else if(x<=get_size(p->lc)+p->val){
			return p->key;
		}else{
			return at(p->rc,x-get_size(p->lc)-p->val);
		}
	}

	ll at(ll x){
		return at(root,x);
	}

	ll prev(node* p,ll k){
		if(!p){
			return LLONG_MIN;
		}
		if(k<=p->key){
			return prev(p->lc,k);
		}else{
			return max(p->key,prev(p->rc,k));
		}
	}

	ll prev(ll k){
		return prev(root,k);
	}

	ll next(node* p,ll k){
		if(!p){
			return LLONG_MAX;
		}
		if(k>=p->key){
			return next(p->rc,k);
		}else{
			return min(p->key,next(p->lc,k));
		}
	}

	ll next(ll k){
		return next(root,k);
	}

	node* remove(node* p,ll k){
		if(k<p->key){
			p->lc=remove(p->lc,k);
		}else if(k>p->key){
			p->rc=remove(p->rc,k);
		}else{
			if(p->val>1){
				p->val--;
			}else{
				if(!p->lc&&!p->rc){
					delete p;
					return nullptr;
				}else if(p->lc&&!p->rc){
					node* tmp=p;
					p=p->lc;
					delete tmp;
				}else if(!p->lc&&p->rc){
					node* tmp=p;
					p=p->rc;
					delete tmp;
				}else{
					if(get_priority(p->lc)>=get_priority(p->rc)){
						p=right_rotate(p);
						p->rc=remove(p->rc,k);
					}else{
						p=left_rotate(p);
						p->lc=remove(p->lc,k);
					}
				}
			}
		}
		up(p);
		return p;
	}

	void remove(ll k){
		if(get_rank(k)!=get_rank(k+1)){
			root=remove(root,k);
		}
	}
};