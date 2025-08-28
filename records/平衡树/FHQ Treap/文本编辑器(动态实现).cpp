//https://www.luogu.com.cn/problem/P4008
//@@@
//balanced tree(FHQ Treap)
//FHQ-Treap实现区间移动
//getchar() 和 ios::sync_with_stdio(false);水火不相容
//getchar() 和 ios::sync_with_stdio(false);水火不相容
//getchar() 和 ios::sync_with_stdio(false);水火不相容
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

struct node{
		char key;
		ll val;
		node* lc;
		node* rc;
		ll sz;
		ll priority;
		node(ll key):key(key),val(1),lc(nullptr),rc(nullptr),sz(1),priority(ran(1,100000)){}
	};
class FHQ_treap{
public:
	node* root=nullptr;
	vector<node*> mp={nullptr};
	ll cnt=0;

	node* new_node(ll key){
		node* p=new node(key);
		mp.push_back(p);
		return p;
	}

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
        if(get_size(p->lc)+1<=t){
			l=p;
            split(p->rc,t-get_size(p->lc)-1,p->rc,r);
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

	string inorder(node* rt){
		string res;
		function<void(node*)> dfs=[&](node* p)->void{
			if(!p) return;
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
	ll n;
	cin>>n;
	ll pos;
	for(ll i=1;i<=n;i++){
		string op;
		cin>>op;
		if(op=="Prev"){
			pos--;
		}else if(op=="Next"){
			pos++;
		}else if(op=="Move"){
			cin>>pos;
		}else if(op=="Insert"){
			ll len;
			cin>>len;
			node* l=nullptr;
			node* r=nullptr;
			fhq.split(fhq.root,pos,l,r);
			for(ll j=1;j<=len;j++){
				char ch;
				ch=getchar();
				while(ch<32||ch>126){
					ch=getchar();
				}
				node* e=new node(ch);
				l=fhq.merge(l,e);
			}
			fhq.root=fhq.merge(l,r);
		}else if(op=="Delete"){
			ll len;
			cin>>len;
			node* lm=nullptr;
			node* r=nullptr;
			fhq.split(fhq.root,pos+len,lm,r);
			node* l=nullptr;
			node* m=nullptr;
			fhq.split(lm,pos,l,m);
			fhq.root=fhq.merge(l,r);
		}else{
			ll len;
			cin>>len;
			node* lm=nullptr;
			node* r=nullptr;
			fhq.split(fhq.root,pos+len,lm,r);
			node* l=nullptr;
			node* m=nullptr;
			fhq.split(lm,pos,l,m);
			string ans=fhq.inorder(m);
			fhq.root=fhq.merge(fhq.merge(l,m),r);
			cout<<ans<<endl;
		}
	}
	
}

signed main(){
    //ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
	while(T--){
		solve();
	}
    return 0;
}