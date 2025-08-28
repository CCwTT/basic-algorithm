# ACM模板分类整理

## 数据结构

### AVL树.cpp
```cpp
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

//https://www.luogu.com.cn/problem/P3369
//@@@
//avl
class AVL{
public:
    struct Node{
        ll key;
        ll val;
        Node* lc;
        Node* rc;
        ll height;
        ll sz; 
    };
    Node* root=nullptr;

    ll get_height(Node* p){
        if(!p) return 0;
        return p->height;
    }
    
    ll get_size(Node* p){
        if(!p) return 0;
        return p->sz;
    }

    void up(Node* p){
        p->height = max(get_height(p->lc), get_height(p->rc)) + 1;
        p->sz = get_size(p->lc) + get_size(p->rc) + p->val;
    }

    Node* left_rotate(Node* p){
        Node* tmp = p->rc;
        p->rc = tmp->lc;
        tmp->lc = p;
        up(p);
        up(tmp);
        return tmp;
    }

    Node* right_rotate(Node* p){
        Node* tmp = p->lc;
        p->lc = tmp->rc;
        tmp->rc = p;
        up(p);
        up(tmp);
        return tmp;
    }

    Node* ll_rotate(Node* p){
        return right_rotate(p);
    }

    Node* rr_rotate(Node* p){
        return left_rotate(p);
    }

    Node* lr_rotate(Node* p){
        p->lc = left_rotate(p->lc);
        return right_rotate(p);
    }

    Node* rl_rotate(Node* p){
        p->rc = right_rotate(p->rc);
        return left_rotate(p);
    }

    Node* maintain(Node* p){
        if(get_height(p->lc) - get_height(p->rc) > 1){
            if(get_height(p->lc->lc) >= get_height(p->lc->rc)){
                return ll_rotate(p);
            } else {
                return lr_rotate(p);
            }
        } else if(get_height(p->rc) - get_height(p->lc) > 1){
            if(get_height(p->rc->rc) >= get_height(p->rc->lc)){
                return rr_rotate(p);
            } else {
                return rl_rotate(p);
            }
        }
        return p;
    }

    Node* insert(Node* p,ll x){
        if(!p){
            p=new Node;
            p->key=x;
            p->val=1;
            p->lc=p->rc=nullptr;
            p->height=1;
            p->sz=1;
            return p;
        }
        if(x==p->key){
            p->val++;
        }else if(x<p->key){
            p->lc=insert(p->lc,x);
        }else{
            p->rc=insert(p->rc,x);
        }
        up(p);
        return maintain(p);
    }

    void insert(ll x){
        root=insert(root,x);
    }

    ll get_rank(Node* p,ll x){
        if(!p) return 1;
        if(x==p->key) return get_size(p->lc)+1;
        else if(x<p->key) return get_rank(p->lc,x);
        else return get_size(p->lc)+p->val+get_rank(p->rc,x);
    }

    ll get_rank(ll x){
        return get_rank(root,x);
    }

    pair<Node*,Node*> remove_leftmost(Node* p){
        if(!p) return {nullptr,nullptr};
        if(!p->lc) return {p->rc,p};
        auto [nlc,lm]=remove_leftmost(p->lc);
        p->lc=nlc;
        up(p);
        return {maintain(p),lm};
    }

    Node* remove(Node* p,ll x){
        if(x==p->key){
            if(p->val>1){
                p->val--;
            }else{
                if(!p->lc&&!p->rc){
                    return nullptr;
                }else if(p->lc&&!p->rc){
                    return p->lc;
                }else if(p->rc&&!p->lc){
                    return p->rc;
                }else{
                    auto [nrc,np]=remove_leftmost(p->rc);
                    np->lc=p->lc;
                    np->rc=nrc;
                    p=np;
                }
            }
        }else if(x<p->key){
            p->lc=remove(p->lc,x);
        }else{
            p->rc=remove(p->rc,x);
        }
        up(p);
        return maintain(p);
    }

    void remove(ll x){
        if(get_rank(x)!=get_rank(x+1)){
            root=remove(root,x);
        }
    }

    ll at(Node* p,ll x){ //rank->key rank is 1-indexed
        if(get_size(p->lc)>=x){
            return at(p->lc,x);
        }else if(get_size(p->lc)+p->val>=x){
            return p->key;
        }else{
            return at(p->rc,x-get_size(p->lc)-p->val);
        }
    }

    ll at(ll x){
        if(x<=0) return LLONG_MIN;
        if(x>get_size(root)) return LLONG_MAX;
        return at(root,x);
    }

    ll prev(Node* p,ll x){
        if(!p) return LLONG_MIN;
        if(x<=p->key){
            return prev(p->lc,x);
        }else{
            return max(p->key,prev(p->rc,x));
        }
    }

    ll prev(ll x){
        return prev(root,x);
    }

    ll next(Node* p,ll x){
        if(!p) return LLONG_MAX;
        if(x>=p->key){
            return next(p->rc,x);
        }else{
            return min(p->key,next(p->lc,x));
        }
    }

    ll next(ll x){
        return next(root,x);
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    AVL avl;
    ll n;
    cin>>n;
    for(ll i=0;i<n;i++){
        ll op,x;
        cin>>op>>x;
        if(op==1){
            avl.insert(x);
        }else if(op==2){
            avl.remove(x);
        }else if(op==3){
            cout<<avl.get_rank(x)<<endl;
        }else if(op==4){
            cout<<avl.at(x)<<endl;
        }else if(op==5){
            cout<<avl.prev(x)<<endl;
        }else{
            cout<<avl.next(x)<<endl;
        }
    }
    return 0;
}

```

### BIT.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;

template <class T> class BIT{
	int n;
	vector<T> c;
	
public:
	BIT(int n){
		this->n=n;
		c=vector<T>(n+1);
	}
	
	assign(int n){
		this->n=n;
		c=vector<T>(n+1);
	}
	
	clear(){
		c=vector<T>(n+1);
	}

	void add(int i,T delta){
		for(;i<=n;i+=i&(-i))
			c[i]+=delta;
	}
	
	void set(int i,T val){
		add(i,val-c[i]);
	}

	T sum(int i){
		T ret=0;
		for(;i;i&=(i-1))
			ret+=c[i];
		return ret;
	}
	
	T sum(int i,int j){
		return sum(j)-sum(i-1);
	}

	//weighted fenwick tree query kth smallest value(1-indexed)
	//@?
	T query_kth(int k){
		ll x=0,acc=0;
		for(ll i=1<<__lg(n);i;i>>=1){
			if(x+i<=n&&cur+c[x+i]<=k){
				x+=i;
				acc+=c[x];
			}
		}
		return x;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	vector<int> a={400,800,200,500,-1000000,600,900,100,100};
	auto disc=a;
	sort(disc.begin(),disc.end());
	disc.erase(unique(disc.begin(),disc.end()),disc.end()); 
	unordered_map<int,int> pos;
	for(int i=0;i<a.size();i++){
		pos[a[i]]=lower_bound(disc.begin(),disc.end(),a[i])-disc.begin()+1;
	}
	
	vector<int> leftSmallerCnt(a.size());
	vector<int> leftBiggerCnt(a.size());
	vector<int> rightSmallerCnt(a.size());
	vector<int> rightBiggerCnt(a.size());
	BIT<int> fenwick(a.size()+1);
	for(int i=0;i<a.size();i++){
		leftSmallerCnt[i]=fenwick.sum(pos[a[i]]-1);
		leftBiggerCnt[i]=i-fenwick.sum(pos[a[i]]);
		fenwick.add(pos[a[i]],1);
	}
	fenwick.clear();
	for(int i=a.size()-1;i>=0;i--){
		rightSmallerCnt[i]=fenwick.sum(pos[a[i]]-1);
		rightBiggerCnt[i]=a.size()-i-fenwick.sum(pos[a[i]]);
		fenwick.add(pos[a[i]],1);
	}
	cout<<"leftSmallerCnt: ";
	for(int i=0;i<a.size();i++) cout<<leftSmallerCnt[i]<<" "; 
	cout<<endl;
	cout<<"leftBiggerCnt: ";
	for(int i=0;i<a.size();i++) cout<<leftBiggerCnt[i]<<" "; 
	cout<<endl;
	cout<<"rightSmallerCnt: ";
	for(int i=0;i<a.size();i++) cout<<rightSmallerCnt[i]<<" "; 
	cout<<endl;
	cout<<"rightBiggerCnt: ";
	for(int i=0;i<a.size();i++) cout<<rightBiggerCnt[i]<<" "; 
	cout<<endl;
	return 0;
} 

```

### Dsu.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//groups function see functional tree 
class Dsu{
private:
	vector<int> f;
	vector<int> rank;
	
public:
	Dsu(int n):f(n),rank(n,0){
		iota(f.begin(),f.end(),0);
	}
	
	int find(int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	
	void join(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return;
		if(rank[fx]<rank[fy]){
			f[fx]=fy;
		}else if(rank[fx]>rank[fy]){
			fy=fx;
		}else{
			f[fy]=fx;
			rank[fx]++;
		}
	}
	
	bool check(int x,int y){
		return find(x)==find(y);
	}
};

//@@@
class Dsu{
public:
	vector<ll> f;
	Dsu(ll n):f(n){
		iota(f.begin(),f.end(),0);
	}
	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	bool check(ll x,ll y){
		return find(x)==find(y);
	}
	void join(ll x,ll y){
		if(!check(x,y)) f[find(y)]=find(x);
	}
};

class WDsu{
public:
	vector<ll> f;
	vector<ll> dist;

	WDsu(ll n):f(n),dist(n){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		ll _fx=f[x];
		return f[x]==x?x:(f[x]=find(f[x]),dist[x]+=dist[_fx],f[x]);
	}

	//y is the referenced system
	void join(ll x,ll y,ll v){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		dist[fy]=v+dist[x]-dist[y];
		f[fy]=fx;
	}

	bool check(ll x,ll y){
		return find(x)==find(y);
	}

	ll query(ll x,ll y){
		return check(x,y)?dist[y]-dist[x]:LLONG_MAX;
	}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}

```

### fhq-treap.cpp
```cpp
//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(FHQ treap) model
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l,ll r){
	return l+rng()%(r-l+1);
}

const ll MAXN=1e5+5;
const ll MAXT=MAXN*50;
ll root=0;
ll cnt=0;
ll lc[MAXT];
ll rc[MAXT];
ll key[MAXT];
ll sz[MAXT];
ll priority[MAXT];

ll create(ll k){
	ll p=++cnt;
	lc[p]=0;
	rc[p]=0;
	key[p]=k;
	sz[p]=1;
	priority[p]=rnd(1,1e5);
	return p;
}

void up(int p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll div,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	if(key[p]<=div){
		l=p;
		split(rc[p],div,rc[l],r);
	}else{
		r=p;
		split(lc[p],div,l,lc[r]);
	}
	up(p);
}

ll merge(ll l,ll r){
	if(!l||!r){
		return l+r;
	}
	if(priority[l]>=priority[r]){
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

ll insert(ll k){
	ll l=0;
	ll r=0;
	split(root,k,l,r);
	ll e=create(k);
	return merge(merge(l,e),r);
}

ll remove(ll k){
	ll lm=0;
	ll r=0;
	split(root,k,lm,r);
	ll l=0;
	ll m=0;
	split(lm,k-1,l,m);
	return merge(merge(l,merge(lc[m],rc[m])),r);
}

ll small(ll p,ll k){
	if(!p) return 0;
	if(k<=key[p]) return small(lc[p],k);
	return sz[lc[p]]+1+small(rc[p],k);
}

ll get_rank(ll k){
	return small(root,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+1) return p;
	return at(rc[p],x-sz[lc[p]]-1);
}

ll at(ll x){
	return at(root,x);
}

ll prev(ll p,ll k){
	if(!p) return INT_MIN+1;
	if(k<=key[p]) return prev(lc[p],k);
	return max(key[p],prev(rc[p],k));
}

ll next(ll p,ll k){
	if(!p) return INT_MAX;
	if(k>=key[p]) return next(rc[p],k);
	return min(key[p],next(lc[p],k));
}

void solve(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			root=insert(x);
		}else if(op==2){
			root=remove(x);
		}else if(op==3){
			cout<<get_rank(x)<<endl;
		}else if(op==4){
			cout<<key[at(x)]<<endl;
		}else if(op==5){
			cout<<prev(x)<<endl;
		}else{
			cout<<next(x)<<endl;
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

```

### fhq-treap_persistent.cpp
```cpp
//https://www.luogu.com.cn/problem/P3835
//@@@
//balanced tree(fhq-treap)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l,ll r){
	return l+rng()%(r-l+1);
}

const ll MAXN=5e5+5;
const ll MAXT=MAXN*50;

ll root[MAXN];
ll cnt=0;
ll lc[MAXT];
ll rc[MAXT];
ll priority[MAXT];
ll key[MAXT];
ll sz[MAXT];

ll create(ll k){
	ll p=++cnt;
	lc[p]=rc[p]=0;
	priority[p]=rnd(1,1e9);
	key[p]=k;
	sz[p]=1;
	return p;
}

ll clone(ll p){
	ll q=++cnt;
	lc[q]=lc[p];
	rc[q]=rc[p];
	priority[q]=priority[p];
	key[q]=key[p];
	sz[q]=sz[p];
	return q;
}

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll div,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	p=clone(p);
	if(key[p]<=div){
		l=p;
		split(rc[p],div,rc[l],r);
	}else{
		r=p;
		split(lc[p],div,l,lc[r]);
	}
	up(p);
}

ll merge(ll l,ll r){
	if(l==0||r==0){
		return l+r;
	}
	if(priority[l]>=priority[r]){
		l=clone(l);
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		r=clone(r);
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

ll insert(ll p,ll k){
	ll l=0;
	ll r=0;
	split(p,k,l,r);
	ll e=create(k);
	return merge(merge(l,e),r);
}

ll remove(ll p,ll k){
	ll lm=0;
	ll r=0;
	split(p,k,lm,r);
	ll l=0;
	ll m=0;
	split(lm,k-1,l,m);
	return merge(merge(l,merge(lc[m],rc[m])),r);
}

ll small(ll p,ll k){
	if(!p) return 0;
	if(k<=key[p]) return small(lc[p],k);
	return sz[lc[p]]+1+small(rc[p],k);
}

ll get_rank(ll p,ll k){
	return small(p,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+1) return p;
	return at(rc[p],x-sz[lc[p]]-1);
}

ll prev(ll p,ll k){
	if(!p) return INT_MIN+1;
	if(k<=key[p]) return prev(lc[p],k);
	return max(key[p],prev(rc[p],k));
}

ll next(ll p,ll k){
	if(!p) return INT_MAX;
	if(k>=key[p]) return next(rc[p],k);
	return min(key[p],next(lc[p],k));
}

void solve(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll vs,op,x;
		cin>>vs>>op>>x;
		if(op==1){
			root[i]=insert(root[vs],x);
		}else if(op==2){
			root[i]=remove(root[vs],x);
		}else if(op==3){
			root[i]=root[vs];
			cout<<get_rank(root[vs],x)<<endl;
		}else if(op==4){
			root[i]=root[vs];
			cout<<key[at(root[vs],x)]<<endl;
		}else if(op==5){
			root[i]=root[vs];
			cout<<prev(root[vs],x)<<endl;
		}else{
			root[i]=root[vs];
			cout<<next(root[vs],x)<<endl;
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

```

### ST.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class ST{
	vector<vector<ll>> st;
public:
	ST(vector<ll>& a){
		ll n=a.size();
		ll high=__lg(n-1-0+1);
		st.assign(n,vector<ll>(high+1));
		for(ll i=0;i<n;i++){
			st[i][0]=a[i];
		}
		for(ll j=1;j<=high;j++){
			for(ll i=0;i<=n-(1<<j);i++){
				st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
		}
	}
	
	ll query(ll x,ll y){
		ll high=__lg(y-x+1);
		return max(st[x][high],st[y-(1<<high)+1][high]);
	}
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
  	vector<ll> a={5,3,7,2,12,1,6,4,8,15};
  	ST st(a);
  	for(ll i=0;i<a.size();i++){
  		for(ll j=i;j<a.size();j++){
  			cout<<i<<" to "<<j<<" :"<<st.query(i,j)<<endl;
		}
	}
    return 0;
}

```

### Treap.cpp
```cpp
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
```

### Trie.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//realization of class
//@@@
class Trie {
    ll pass;
    ll ed;
    Trie* ch[26];
public:
    Trie():pass(0),ed(0),ch(){}
    
    void insert(string word) {
        Trie* p=this;
        //p->pass++;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                p->ch[x]=new Trie();
            }
            p=p->ch[x];
            p->pass++;
        }    
        p->ed++;
    }

    ll erase(string word) {
        Trie* p=this;
        //p->pass--;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return -1;
            }
            p=p->ch[x];
            p->pass--;
        }
        p->ed--;
        return 0;
    }
    
    ll count(string word) {
        Trie* p=this;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return 0;
            }
            p=p->ch[x];
        }
        return p->ed;
    }
    
    ll count_prefix(string prefix) {
        Trie* p=this;
        for(char c:prefix){
            ll x=c-'a';
            if(!p->ch[x]){
                return 0;
            }
            p=p->ch[x];
        }
        return p->pass;
    }
};

//realization of class(unordered_map) @@@
class Trie {
    typedef long long ll;
    ll pass;
    ll ed;
    unordered_map<ll,Trie*> ch;
public:
    Trie():pass(0),ed(0) {}

    void insert(string word) {
        Trie* p=this;
        p->pass++;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch.count(x)){
                p->ch[x]=new Trie();
            }
            p=p->ch[x];
            p->pass++;
        }
        p->ed++;
    }
    
    ll count(string word) {
        Trie* p=this;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch.count(x)){
                return 0;
            }
            p=p->ch[x];
        }
        return p->ed;
    }
    
    ll count_prefix(string prefix) {
        Trie* p=this;
        for(char c:prefix){
            ll x=c-'a';
            if(!p->ch.count(x)){
                return 0;
            }
            p=p->ch[x];
        }
        return p->pass;
    }
    
    ll erase(string word) {
        Trie* p=this;
        p->pass--;
        for(auto c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return -1;
            }
            p=p->ch[x];
            p->pass--;
        }
        p->ed--;
        return 0;
    }
};

//static array @@@
const ll MAXN=150001;
ll ch[MAXN][26];
ll pass[MAXN],ed[MAXN];
ll cnt;

void init(){
    cnt=0;
}

void insert(string word){
    ll p=0;
    pass[p]++;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x]==0){
            ch[p][x]=++cnt;
        }
        p=ch[p][x];
        pass[p]++;
    }
    ed[p]++;
}

ll count(string word){
    ll p=0;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x]==0){
            return 0;
        }
        p=ch[p][x];
    }
    return ed[p];
}

ll count_prefix(string prefix){
    ll p=0;
    for(auto c:prefix){
        ll x=c-'a';
        if(ch[p][x]==0){
            return 0;
        }
        p=ch[p][x];
    }
    return pass[p];
}

ll erase(string word) {
    ll p=0;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x])
        p=ch[p][x];
        pass[p]--;
    }
    ed[p]--;
    return 0;
}

void clear(){
    for(ll i=0;i<=cnt;i++){
        memset(ch[i],0,sizeof(ch[i]));
        pass[i]=ed[i]=0;
    }
} 

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}
```

## 字符串

### KMP.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/621958042/
//@@@
vector<ll> get_next(string s){ 
	ll n=s.size();
	vector<ll> next(n+1);
	next[0]=-1;
	next[1]=0;
	ll i=2,j=0;
	while(i<=n){
		if(s[i-1]==s[j]){
			next[i++]=++j;
		}else if(j){
			j=next[j];
		}else{
			next[i++]=0;
		}
	}
	return next;
}

ll kmp(string s,string t){ //vector<ll> s,vector<ll> t
	ll m=s.size(),n=t.size();
	auto next=get_next(t);
	ll i=0,j=0;
	while(i<m&&j<n){
		if(s[i]==t[j]){
			i++,j++;
		}else if(j){
			j=next[j];
		}else{
			i++;
		}
	}
	return j==n?i-j:-1;
}

//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/621958042/
//@@@
//1-indexed
vector<ll> get_next(string s){
	ll n=s.size()-1;
	vector<ll> next(n+2);
	next[0]=0;
	next[1]=0;
    next[2]=1;
	ll i=3,j=1;
	while(i<=n+1){
		if(s[i-1]==s[j]){
			next[i++]=++j;
		}else if(j>1){
			j=next[j];
		}else{
			next[i++]=1;
		}
	}
	return next;
} 

ll kmp(string s,string t){
	ll m=s.size()-1,n=t.size()-1;
	auto next=get_next(t);
	ll i=1,j=1;
	while(i<=m&&j<=n){
		if(s[i]==t[j]){
			i++,j++;
		}else if(j>1){
			j=next[j];
		}else{
			i++;
		}
	}
	return j==n+1?i-j+1:0;
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string s="abcdefgh",t="def";
	cout<<kmp(s,t); 
    return 0;
}
```

### Manacher和Z函数.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string pre_process(string s){
	string res="#";
	ll n=s.size();
	for(ll i=0;i<n;i++){
		res.push_back(s[i]);
		res.push_back('#');
	}
	return res;
}

//2025/6/23
vector<ll> get_p(string s){ //p:palindrome the length of the wing of the processed string
	ll n=s.size();
	vector<ll> p(n);
	ll boxr=0,boxm=0;   
	for(ll i=0;i<n;i++){
		p[i]=i<boxr?min(boxr-i,p[2*boxm-i]):1;
		while(i-p[i]>=0&&i+p[i]<n&&s[i-p[i]]==s[i+p[i]]){
			p[i]++;
		}
		if(i+p[i]>boxr){
			boxr=i+p[i];
			boxm=i;
		}
	}
	return p;
}

vector<ll> get_z(string s){ //LCP of every suffix of s and s 
	ll n=s.size();
	vector<ll> z(n);
	z[0]=n;
	for(ll i=1,boxl=1,boxr=1;i<n;i++){  //box:[)
		z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
			z[i]++;
		}
		if(i+z[i]>boxr){
			boxr=i+z[i];
			boxl=i;
		}
	}
	return z;
}

vector<ll> get_e(string s,string t){ //LCP of every suffix of s and t
	ll m=s.size(),n=t.size();
	auto z=get_z(t);
	vector<ll> e(m);
	for(ll i=0,boxl=0,boxr=0;i<m;i++){
		e[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+e[i]<m&&e[i]<n&&s[i+e[i]]==t[e[i]]){
			e[i]++;
		}
		if(i+e[i]>boxr){
			boxr=i+e[i];
			boxl=i;
		}
	}
	return e;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	string s="afsdlaabaakelq";
	auto ss=pre_process(s);
	auto p=get_p(ss); 
	cout<<*max_element(p.begin(),p.end())-1;
    return 0;
}
```

## 数学

### 中国剩余定理及其扩展.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//扩展欧几里得=gcd(a,b) (可求逆元) 
ll exgcd(ll a,ll b,ll& x,ll& y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll x1,y1;
	ll d=exgcd(b,a%b,x1,y1);
	x=y1,y=x1-a/b*y1;
	return d;
}
tuple<ll,ll,ll> exgcd(ll a,ll b){
	if(b==0) return {a,1,0};
	auto [d,x,y]=exgcd(b,a%b);
	return {d,y,x-a/b*y};
}

//中国剩余定理(同余方程组) 
ll crt(vector<ll>& r,vector<ll>& m){
	ll lcm=1,res=0;
	ll n=m.size();
	for(ll i=0;i<n;i++) lcm*=m[i]; //先求lcm再做除法防止爆ll
	for(ll i=0;i<n;i++){
		ll c=lcm/m[i],inv_c,tmp;
		exgcd(c,m[i],inv_c,tmp); //注意inv_c可能为负!!!
		res=(res+r[i]*c%lcm*inv_c%lcm)%lcm;
	} 
	return (res%lcm+lcm)%lcm;
}

//扩展中国剩余定理 (?)
//r.size()>=2
ll excrt(vector<ll>& r,vector<ll>& m){
	ll n=r.size();
	ll r1,r2,m1,m2,x0,y0,x,y;
	r1=r[0],m1=m[0];
	for(ll i=1;i<n;i++){
		ll d=exgcd(m1,m2,x0,y0);
		if((r2-r1)%d!=0){
			return -1;
		}
		x=x*(r2-r1)/d;
		x=(x%(m2/d)+m2/d)%(m2/d);
		r1=m1*p+r1;
		m1=m1*m2/d;
	}
	return (r1%m1+m1)%m1;
} 

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}
```

## 图论

### 二分图.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//@@@
//https://acm.tju.edu.cn/group/1010/problem/2025TJUACM3-1021
//if bipartite return 1,else return 0
bool check_bipartite(vector<vector<ll>>& g){
	ll n=g.size();
	vector<ll> color(n,-1);
	function<bool(ll,ll)> dfs=[&](ll x,ll c)->bool{
		color[x]=c;
		for(auto& y:g[x]){
			if(!~color[y]&&!dfs(y,1-c)||color[y]==c){
				return false;
			}
		} 
		return true;
	};
	for(ll i=0;i<n;i++){
		if(!~color[i]&&!dfs(i,0)){
			return false;
		}
	}
	return true;
}


signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	return 0;
} 
```

### 单调栈.cpp
```cpp
#include<bits/stdc++.h>
using namespace std;

//https://codeforces.com/contest/2090/problem/E1
/*

rnear: find the smallest j>i s.t. pred1(j)</<=/>/>=pred2(i);
vector<ll> rnear(n+1,n+1);
stack<ll> stk;
for(ll i=n;i>=1;i--){
    while(!stk.empty()&&pred1(stk.top())>=/>/<=/<pred2(i)){
        stk.pop();
    }
    if(!stk.empty()) rnear[i]=stk.top();
    stk.push(i);
}

lnear: find the biggest j<i s.t. pred1(j)</<=/>/>=pred2(i);
vector<ll> lnear(n+1,0);
stack<ll> stk;
for(ll i=1;i<=n;i++){
    while(!stk.empty()&&pred1(stk.top())>=/>/<=/<pred2(i)){
        stk.pop();
    }
    if(!stk.empty()) lnear[i]=stk.top();
    stk.push(i);
}

*/

vector<int> getLeftNearestSmaller(vector<int>& a){
    int n=a.size();
    vector<int> ret(n);
    stack<int> stk;
    for(int i=0;i<n;i++){
        while(!stk.empty()&&a[stk.top()]>=a[i]){
            stk.pop();
        }
        ret[i]=stk.empty()?-1:stk.top();
        stk.push(i);
    }
    return ret;
}

vector<int> getRightNearestSmaller(vector<int>& a){
    int n=a.size();
    vector<int> ret(n);
    stack<int> stk;
    for(int i=n-1;i>=0;i--){
        while(!stk.empty()&&a[stk.top()]>=a[i]){
            stk.pop();
        }
        ret[i]=stk.empty()?-1:stk.top();
        stk.push(i);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
  	
    return 0;
}
```

### 单调队列.cpp
```cpp
//@@@
deque<ll> dq;
for(ll i=0;i<n;i++){
    while(!dq.empty()&&a[dq.back()]<=a[i]){
        dq.pop_back();
    }
    dq.push_back(i);
    while(dq.front()<=i-k){
        dq.pop_front();
    }

    ...
    
}
```
