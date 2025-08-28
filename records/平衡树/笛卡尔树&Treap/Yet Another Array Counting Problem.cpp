//https://codeforces.com/problemset/problem/1748/E
//@@@
//Cartesian tree
//笛卡尔树单调栈，压下去则为上！
//同级最左为上则从左到右建笛卡尔树，同级最右为上则从右往左建笛卡尔树
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

const ll mod=1e9+7;

class Cartesian_tree{
public:
	struct node{
		ll key;
		ll val;
		node* lc;
		node* rc;
		ll id;
		node(){}
		node(ll key,ll val):key(key),val(val),lc(nullptr),rc(nullptr){}
	};
	node* root=nullptr;
	stack<node*> stk;
	ll cnt=0;

	void insert(ll k,ll v){
		node* p=new node(k,v);
		p->id=++cnt;
		if(!root){
			root=p;
			stk.push(p);
			return;
		}
		node* last=nullptr;
		while(!stk.empty()&&stk.top()->val<v){ //同级最左为上则没有等号
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

ll get_id(Cartesian_tree::node* p){
	return p?p->id:0;
}

void solve(){
	Cartesian_tree ct;
	ll n,m;
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		ct.insert(i,x);
	}
	vector<vector<ll>> f(n+1,vector<ll>(m+1,0));
	for(ll j=0;j<=m;j++){
		f[0][j]=1;
	}
	function<void(Cartesian_tree::node*)> dfs=[&](Cartesian_tree::node* p)->void{
		if(!p) return;
		dfs(p->lc);
		dfs(p->rc);
		vector<ll> tmp(m+1);
		for(ll j=1;j<=m;j++){
			tmp[j]=f[get_id(p->lc)][j-1]*f[get_id(p->rc)][j]%mod;
		}
		for(ll j=1;j<=m;j++){
			f[p->id][j]=(tmp[j]+f[p->id][j-1])%mod;
		}
	};
	dfs(ct.root);
	cout<<f[ct.root->id][m]<<endl;
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
	cin>>T;
    while(T--){
        solve();
    }
    return 0;
}

