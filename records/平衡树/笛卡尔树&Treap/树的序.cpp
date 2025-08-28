//https://www.luogu.com.cn/problem/P1377
//@@@
//balanced tree(treap)
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

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return l+RNG()%(r-l+1);
}

class descartes_tree{
public:
	struct Node{
		ll key;
		ll val;
		Node* lc;
		Node* rc;
		Node(){}
		Node(ll key,ll val):key(key),val(val),lc(nullptr),rc(nullptr){}
	};
	Node* root=nullptr;
	stack<Node*> stk;

	void insert(ll k,ll v){
		Node* p=new Node(k,v);
		if(!root){
			root=p;
			stk.push(p);
			return;
		}
		Node* last=nullptr;
		while(!stk.empty()&&stk.top()->val>v){
			last=stk.top();
			stk.pop();
		}
		if(!stk.empty()){
			stk.top()->rc=p;
		}
		if(last){
			p->lc=last;
			if(last==root){
				root=p;
			}
		}
		stk.push(p);
	}
};

void solve(){
	descartes_tree dt;
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		a[x]=i;
	}
	for(ll i=1;i<=n;i++){
		dt.insert(i,a[i]);
	}
	vector<ll> ans;
	function<void(descartes_tree::Node*)> preorder=[&](descartes_tree::Node* p){
		if(!p) return;
		ans.push_back(p->key);
		preorder(p->lc);
		preorder(p->rc);
	};
	preorder(dt.root);
	for(ll i=0;i<ans.size();i++){
		cout<<ans[i]<<" ";
	}
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}

