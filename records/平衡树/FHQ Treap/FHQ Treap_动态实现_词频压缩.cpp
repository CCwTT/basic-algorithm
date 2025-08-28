//https://luogu.com.cn/record/221935289
//@@@
//balanced tree(FHQ Treap)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>&a){
	cout<<"Log:";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return l+RNG()%(r-l+1);
}

class FHQ_treap{
public:
    struct node{
		ll key;
		ll val;
		node* lc;
		node* rc;
		ll sz;
		ll priority;
		node(ll key):key(key),val(1),lc(nullptr),rc(nullptr),sz(1),priority(ran(1,100000)){}
	};

	node* root=nullptr;

	ll get_size(node* p){
		return p?p->sz:0;
	}

	void up(node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+p->val;
	}

    void split(node* p,ll t,node*& l,node*& r){
        if(!p){
            l=r=nullptr;
            return;
        }
        if(p->key<=t){
			l=p;
            split(p->rc,t,p->rc,r);
        }else{
			r=p;
            split(p->lc,t,l,p->lc);
        }
        up(p);
    }

    node* merge(node* l,node* r){
        if(!l||!r) return l?l:r?r:nullptr;
        if(l->priority>=r->priority){
            l->rc=merge(l->rc,r);
            up(l);
            return l;
        }else{
            r->lc=merge(l,r->lc);
            up(r);
            return r;
        }
    }

    node* find(node* p,ll k){
        if(!p) return nullptr;
        if(k==p->key) return p;
        if(k<p->key) return find(p->lc,k);
        return find(p->rc,k);
    }

    void add_count(node* p,ll k,ll v){
        if(!p) return;
        if(k==p->key){
            p->val+=v;
        }else if(k<p->key){
            add_count(p->lc,k,v);
        }else{
            add_count(p->rc,k,v);
        }
        up(p);
    }

    void insert(ll k){
        if(find(root,k)){
            add_count(root,k,1);
            return;
        }
        node* l=nullptr;
        node* r=nullptr;
        split(root,k,l,r);
        node* e=new node(k);
        root=merge(merge(l,e),r);
    }

    void remove(ll k){
        node* p=find(root,k);
        if(!p) return;
        if(p->val>1){
            add_count(root,k,-1);
        }else{
            node* lm=nullptr;
            node* r=nullptr;
            split(root,k,lm,r);
            node* l=nullptr;
            node* m=nullptr;
            split(lm,k-1,l,m);
            root=merge(l,r);
        }
    }

    ll small(node* p,ll k){
        if(!p) return 0;
        if(k<=p->key) return small(p->lc,k);
        return get_size(p->lc)+p->val+small(p->rc,k);
    }

    ll get_rank(ll k){
        return small(root,k)+1;
    }

    ll at(node* p,ll x){
        if(!p||x<=0||x>get_size(p)) return LLONG_MIN;
        ll left_size=get_size(p->lc);
        if(x<=left_size) return at(p->lc,x);
        if(x<=left_size+p->val) return p->key;
        return at(p->rc,x-left_size-p->val);
    }

    ll at(ll x){
        return at(root,x);
    }

    ll prev(node* p,ll k){
        if(!p) return LLONG_MIN;
        if(p->key>=k) return prev(p->lc,k);
        return max(p->key,prev(p->rc,k));
    }

    ll prev(ll k){
        return prev(root,k);
    }

    ll next(node* p,ll k){
        if(!p) return LLONG_MAX;
        if(p->key<=k) return next(p->rc,k);
        return min(p->key,next(p->lc,k));
    }

    ll next(ll k){
        return next(root,k);
    }
};


void solve(){
	FHQ_treap fhq;
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			fhq.insert(x);
		}else if(op==2){
			fhq.remove(x);
		}else if(op==3){
			cout<<fhq.get_rank(x)<<endl;
		}else if(op==4){
			cout<<fhq.at(x)<<endl;
		}else if(op==5){
			cout<<fhq.prev(x)<<endl;
		}else{
			cout<<fhq.next(x)<<endl;
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