//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(scapegoat tree)
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

class scapegoat_tree{
public:
	static constexpr double ALPHA=0.7;
	struct Node{
		ll key;
		ll val;
		Node* lc;
		Node* rc;
		ll sz;
		ll diff;
		Node(ll key=0):key(key),val(1),lc(nullptr),rc(nullptr),sz(1),diff(1) {}
	};
	Node* root=nullptr;
	vector<Node*> collect;
	Node* top;
	Node* father;
	ll side;

	ll get_size(Node* p){
		return p?p->sz:0;
	}

	ll get_diff(Node* p){
		return p?p->diff:0;
	}

	void up(Node* p){
		p->sz=get_size(p->lc)+get_size(p->rc)+p->val;
		p->diff=get_diff(p->lc)+get_diff(p->rc)+(p->val>0?1:0);
	}

	void inorder(Node* p){
		if(p){
			inorder(p->lc);
			if(p->val>0){
				collect.push_back(p);
			}
			inorder(p->rc);
		}
	}

	Node* build(ll l,ll r){
		if(l>r){
			return 0;
		}
		ll m=(l+r)>>1;
		Node* p=collect[m];
		p->lc=build(l,m-1);
		p->rc=build(m+1,r);
		up(p);
		return p;
	}

	void rebuild(){
		if(top){
			collect.clear();
			inorder(top);
			if(collect.size()){
				if(!father){
					root=build(0,collect.size()-1);
				}else if(side==1){
					father->lc=build(0,collect.size()-1);
				}else{
					father->rc=build(0,collect.size()-1);
				}
			}
		}
	}

	bool balance(Node* p){
		return ALPHA*p->diff>=max(get_diff(p->lc),get_diff(p->rc));
	}

	void insert(Node* p,Node* fa,ll s,ll k){
		if(!p){
			if(!fa){
				root=new Node(k);
			}else if(s==1){
				fa->lc=new Node(k);
			}else{
				fa->rc=new Node(k);
			}
		}else{
			if(k==p->key){
				p->val++;
			}else if(k<p->key){
				insert(p->lc,p,1,k);
			}else{
				insert(p->rc,p,2,k);
			}
			up(p);
			if(!balance(p)){
				top=p;
				father=fa;
				side=s;
			}
		}
	}

	void insert(ll k){
		top=father=nullptr;
		side=0;
		insert(root,nullptr,0,k);
		rebuild();
	}

	ll small(Node* p,ll k){
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

	ll at(Node* p,ll x){
		if(x<=get_size(p->lc)){
			return at(p->lc,x);
		}else if(x>get_size(p->lc)+p->val){
			return at(p->rc,x-get_size(p->lc)-p->val);
		}
		return p->key;
	}

	ll at(ll x){
		return at(root,x);
	}

	ll prev(ll k){
		ll rank=get_rank(k);
		if(rank==1){
			return LLONG_MIN;
		}else{
			return at(rank-1);
		}
	}

	ll next(ll k){
		ll rank=get_rank(k+1);
		if(rank==get_size(root)+1){
			return LLONG_MAX;
		}else{
			return at(rank);
		}
	}

	void remove(Node* p,Node* fa,ll s,ll k){
		if(k==p->key){
			p->val--;
		}else if(k<p->key){
			remove(p->lc,p,1,k);
		}else{
			remove(p->rc,p,2,k);
		}
		up(p);
		if(!balance(p)){
			top=p;
			father=fa;
			side=s;
		}
	}

	void remove(ll k){
		if(get_rank(k)!=get_rank(k+1)){
			top=father=nullptr;
			side=0;
			remove(root,nullptr,0,k);
			rebuild();
		}
	}
};

void solve(){
	scapegoat_tree sgt;
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			sgt.insert(x);
		}else if(op==2){
			sgt.remove(x);
		}else if(op==3){
			cout<<sgt.get_rank(x)<<endl;
		}else if(op==4){
			cout<<sgt.at(x)<<endl;
		}else if(op==5){
			cout<<sgt.prev(x)<<endl;
		}else{
			cout<<sgt.next(x)<<endl;
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
